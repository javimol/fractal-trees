/*
 * viewer.c - Interactive OpenGL/GLUT viewer for a forest of branch-list trees.
 *
 * Uses the fixed-function OpenGL pipeline and GLU quadrics, as the original
 * program did, so it runs on practically any OpenGL implementation.
 *
 * Copyright (c) 2004-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "viewer.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define QUALITY_MIN 1
#define QUALITY_MAX 10
#define RAD2DEG(a) ((a) * 180.0 / M_PI)

/* ------------------------------------------------------------------------- */
/* State                                                                     */
/* ------------------------------------------------------------------------- */

typedef struct {
    float target[3];
    float distance;
    float yaw, pitch;  /* degrees */
} Camera;

static struct {
    ViewerConfig *cfg;
    Camera        camera;
    int           focus;          /* -1 = whole forest, otherwise a tree index */
    int           show_axes;
    int           show_ground;
    GLuint        bark_texture;
    GLUquadric   *quadric;
    GLuint        scene_list;     /* cached display list for the trees */
    int           scene_dirty;
    int           drag_button;
    int           last_x, last_y;
} V;

static const char *mode_names[MODE_COUNT] = {
    "lines", "cylinders", "cylinders + joints", "textured"
};

/* ------------------------------------------------------------------------- */
/* Scene bounds and layout                                                   */
/* ------------------------------------------------------------------------- */

/* Horizontal radius of a tree's footprint around its trunk base. */
static float tree_footprint(const Tree *t)
{
    float r = 0.0f;
    for (int k = 0; k < 3; k += 2) {
        r = fmaxf(r, fabsf(t->bbox_min[k]));
        r = fmaxf(r, fabsf(t->bbox_max[k]));
    }
    return r;
}

void viewer_layout_forest(Tree *trees, int count, unsigned seed)
{
    if (count <= 0)
        return;

    trees[0].offset[0] = trees[0].offset[1] = trees[0].offset[2] = 0.0f;
    if (count == 1)
        return;

    srand(seed);

    /* Big forests: jittered sunflower spiral, so trees spread evenly over a disc. */
    if (count > 8) {
        const float golden_angle = (float)M_PI * (3.0f - sqrtf(5.0f));
        float spacing = 0.0f;  /* spiral step: the mean footprint */
        for (int i = 0; i < count; i++)
            spacing += tree_footprint(&trees[i]);
        spacing /= (float)count;

        for (int i = 0; i < count; i++) {
            float a = i * golden_angle + ((float)rand() / RAND_MAX - 0.5f) * 0.5f;
            float r = spacing * sqrtf(i + 0.5f) * (0.9f + 0.2f * (float)rand() / RAND_MAX);
            trees[i].offset[0] = r * sinf(a);
            trees[i].offset[1] = 0.0f;
            trees[i].offset[2] = r * cosf(a);
        }
        return;
    }

    /* Small forests: tree 0 in the centre, the rest on a jittered ring around it. */
    float ring = 0.0f;
    for (int i = 0; i < count; i++)
        ring = fmaxf(ring, tree_footprint(&trees[i]));
    ring *= 1.4f;

    for (int i = 1; i < count; i++) {
        float jitter_a = ((float)rand() / RAND_MAX - 0.5f) * 0.6f;
        float jitter_r = 0.8f + 0.4f * (float)rand() / RAND_MAX;
        float a = 2.0f * (float)M_PI * (i - 1) / (count - 1) + jitter_a;
        trees[i].offset[0] = ring * jitter_r * sinf(a);
        trees[i].offset[1] = 0.0f;
        trees[i].offset[2] = ring * jitter_r * cosf(a);
    }
}

/* Bounds of the visible trees (all of them, or only the focused one). */
static void visible_bounds(float mn[3], float mx[3])
{
    const ViewerConfig *c = V.cfg;
    for (int k = 0; k < 3; k++) {
        mn[k] = 1e30f;
        mx[k] = -1e30f;
    }
    for (int i = 0; i < c->tree_count; i++) {
        if (V.focus >= 0 && i != V.focus)
            continue;
        const Tree *t = &c->trees[i];
        for (int k = 0; k < 3; k++) {
            float off = V.focus >= 0 ? 0.0f : t->offset[k];
            mn[k] = fminf(mn[k], t->bbox_min[k] + off);
            mx[k] = fmaxf(mx[k], t->bbox_max[k] + off);
        }
    }
    mn[1] = fminf(mn[1], 0.0f);  /* include the ground */
}

static float scene_radius(void)
{
    float mn[3], mx[3];
    visible_bounds(mn, mx);
    float dx = mx[0] - mn[0], dy = mx[1] - mn[1], dz = mx[2] - mn[2];
    return 0.5f * sqrtf(dx * dx + dy * dy + dz * dz);
}

static void camera_reset(void)
{
    float mn[3], mx[3];
    visible_bounds(mn, mx);
    for (int k = 0; k < 3; k++)
        V.camera.target[k] = 0.5f * (mn[k] + mx[k]);
    V.camera.distance = scene_radius() * 2.4f;
    V.camera.yaw = 20.0f;
    V.camera.pitch = 12.0f;
}

/* ------------------------------------------------------------------------- */
/* Drawing                                                                   */
/* ------------------------------------------------------------------------- */

/* Rotates the current matrix so that +Z points along the unit vector d. */
static void align_z_to(const float d[3])
{
    float angle = (float)RAD2DEG(acos(fmax(-1.0, fmin(1.0, d[2]))));
    float ax = -d[1], ay = d[0];  /* (0,0,1) x d */
    if (ax * ax + ay * ay < 1e-12f) {
        if (d[2] < 0.0f)
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        return;
    }
    glRotatef(angle, ax, ay, 0.0f);
}

static void draw_branch_line(const Branch *b)
{
    float tip[3];
    branch_tip(b, tip);
    glVertex3fv(b->base);
    glVertex3fv(tip);
}

static void draw_branch_solid(const Branch *b, int slices, int with_joint, int textured)
{
    glPushMatrix();
    glTranslatef(b->base[0], b->base[1], b->base[2]);
    align_z_to(b->dir);

    if (textured) {
        /* Wrap the bark once around the branch and repeat it along its
         * length so it is not stretched on long branches. */
        float r = fmaxf(b->radius_base, 0.5f);
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glScalef(1.0f, b->length / (2.0f * (float)M_PI * r), 1.0f);
        glMatrixMode(GL_MODELVIEW);
    }

    gluCylinder(V.quadric, b->radius_base, b->radius_tip, b->length, slices, 1);

    if (with_joint && b->radius_tip > 0.0f) {
        if (textured) {
            glMatrixMode(GL_TEXTURE);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
        }
        glTranslatef(0.0f, 0.0f, b->length);
        gluSphere(V.quadric, b->radius_tip, slices, slices / 2 + 2);
    }
    glPopMatrix();
}

static void draw_tree(const Tree *t)
{
    const RenderMode mode = V.cfg->mode;

    if (mode == MODE_LINES) {
        glBegin(GL_LINES);
        for (size_t i = 0; i < t->count; i++)
            draw_branch_line(&t->branches[i]);
        glEnd();
        return;
    }

    int slices = 3 + 2 * (V.cfg->quality - 1);
    int joints = mode == MODE_JOINTS || mode == MODE_TEXTURED;
    int textured = mode == MODE_TEXTURED && V.bark_texture;
    for (size_t i = 0; i < t->count; i++)
        draw_branch_solid(&t->branches[i], slices, joints, textured);

    if (textured) {
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
    }
}

static void build_scene_list(void)
{
    const ViewerConfig *c = V.cfg;
    const RenderMode mode = c->mode;
    const int textured = mode == MODE_TEXTURED && V.bark_texture;

    if (!V.scene_list)
        V.scene_list = glGenLists(1);
    glNewList(V.scene_list, GL_COMPILE);

    if (mode == MODE_LINES) {
        glDisable(GL_LIGHTING);
        glLineWidth(1.5f);
        glColor3f(0.22f, 0.18f, 0.14f);
    } else {
        glEnable(GL_LIGHTING);
        if (textured) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, V.bark_texture);
            glColor3f(1.0f, 1.0f, 1.0f);
        } else {
            glColor3f(0.62f, 0.60f, 0.52f);  /* poplar-grey bark */
        }
    }

    for (int i = 0; i < c->tree_count; i++) {
        if (V.focus >= 0 && i != V.focus)
            continue;
        const Tree *t = &c->trees[i];
        glPushMatrix();
        if (V.focus < 0)
            glTranslatef(t->offset[0], t->offset[1], t->offset[2]);
        draw_tree(t);
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
    glEndList();
    V.scene_dirty = 0;
}

static void draw_ground(void)
{
    float mn[3], mx[3];
    visible_bounds(mn, mx);
    float cx = 0.5f * (mn[0] + mx[0]), cz = 0.5f * (mn[2] + mx[2]);
    float r = scene_radius() * 1.3f;

    glEnable(GL_LIGHTING);
    glColor3f(0.42f, 0.50f, 0.32f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, -0.05f, cz);
    for (int i = 0; i <= 64; i++) {
        float a = 2.0f * (float)M_PI * i / 64;
        glVertex3f(cx + r * cosf(a), -0.05f, cz - r * sinf(a));
    }
    glEnd();
}

static void draw_axes(void)
{
    float len = scene_radius();
    glDisable(GL_LIGHTING);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(0.9f, 0.1f, 0.1f); glVertex3f(0, 0, 0); glVertex3f(len, 0, 0);
    glColor3f(0.1f, 0.7f, 0.1f); glVertex3f(0, 0, 0); glVertex3f(0, len, 0);
    glColor3f(0.1f, 0.2f, 0.9f); glVertex3f(0, 0, 0); glVertex3f(0, 0, len);
    glEnd();
}

static void update_title(void)
{
    char title[160];
    if (V.focus < 0)
        snprintf(title, sizeof title, "Fractal trees - %d trees - %s, quality %d",
                 V.cfg->tree_count, mode_names[V.cfg->mode], V.cfg->quality);
    else
        snprintf(title, sizeof title, "Fractal trees - tree %d (%zu branches) - %s, quality %d",
                 V.focus, V.cfg->trees[V.focus].count, mode_names[V.cfg->mode], V.cfg->quality);
    glutSetWindowTitle(title);
}

static void invalidate(void)
{
    V.scene_dirty = 1;
    update_title();
    glutPostRedisplay();
}

/* ------------------------------------------------------------------------- */
/* Screenshots                                                               */
/* ------------------------------------------------------------------------- */

static int save_ppm(const char *path, int w, int h)
{
    unsigned char *px = malloc((size_t)w * h * 3);
    if (!px)
        return -1;
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, px);

    FILE *f = fopen(path, "wb");
    if (!f) {
        perror(path);
        free(px);
        return -1;
    }
    fprintf(f, "P6\n%d %d\n255\n", w, h);
    for (int y = h - 1; y >= 0; y--)  /* OpenGL rows are bottom-up */
        fwrite(px + (size_t)y * w * 3, 1, (size_t)w * 3, f);
    fclose(f);
    free(px);
    printf("Saved %s\n", path);
    return 0;
}

/* ------------------------------------------------------------------------- */
/* GLUT callbacks                                                            */
/* ------------------------------------------------------------------------- */

static void on_display(void)
{
    int w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);
    float radius = scene_radius();

    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float near_plane = fmaxf(V.camera.distance - radius * 2.0f, V.camera.distance * 0.01f);
    gluPerspective(40.0, (double)w / (h ? h : 1), near_plane, V.camera.distance + radius * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -V.camera.distance);
    glRotatef(V.camera.pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-V.camera.yaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-V.camera.target[0], -V.camera.target[1], -V.camera.target[2]);

    /* Directional "sun", fixed in world space. */
    const GLfloat sun_dir[] = { 0.4f, 1.0f, 0.6f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, sun_dir);

    if (V.show_ground)
        draw_ground();
    if (V.scene_dirty)
        build_scene_list();
    glCallList(V.scene_list);
    if (V.show_axes)
        draw_axes();

    if (V.cfg->screenshot) {
        glFinish();
        int rc = save_ppm(V.cfg->screenshot, w, h);
        exit(rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
    }
    glutSwapBuffers();
}

static void on_reshape(int w, int h)
{
    (void)w;
    (void)h;
    glutPostRedisplay();
}

static void on_mouse(int button, int state, int x, int y)
{
    /* freeglut reports the scroll wheel as buttons 3 (up) and 4 (down). */
    if (state == GLUT_DOWN && (button == 3 || button == 4)) {
        V.camera.distance *= button == 3 ? 0.9f : 1.1f;
        glutPostRedisplay();
        return;
    }
    V.drag_button = state == GLUT_DOWN ? button : -1;
    V.last_x = x;
    V.last_y = y;
}

static void on_motion(int x, int y)
{
    int dx = x - V.last_x, dy = y - V.last_y;
    V.last_x = x;
    V.last_y = y;

    if (V.drag_button == GLUT_LEFT_BUTTON) {
        V.camera.yaw -= dx * 0.4f;
        V.camera.pitch = fmaxf(-89.0f, fminf(89.0f, V.camera.pitch + dy * 0.4f));
    } else if (V.drag_button == GLUT_RIGHT_BUTTON) {
        V.camera.distance *= expf(dy * 0.01f);
    } else if (V.drag_button == GLUT_MIDDLE_BUTTON) {
        float s = V.camera.distance * 0.0015f;
        float yaw = V.camera.yaw * (float)M_PI / 180.0f;
        V.camera.target[0] -= s * dx * cosf(yaw);
        V.camera.target[2] += s * dx * sinf(yaw);
        V.camera.target[1] += s * dy;
    } else {
        return;
    }
    glutPostRedisplay();
}

static void on_key(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
    ViewerConfig *c = V.cfg;

    switch (key) {
    case '0': case '1': case '2': case '3':
        c->mode = (RenderMode)(key - '0');
        if (c->mode == MODE_TEXTURED && !V.bark_texture)
            c->mode = MODE_JOINTS;  /* no texture loaded */
        break;
    case '+': case '=':
        if (c->mode == MODE_LINES)
            c->mode = MODE_CYLINDERS;
        else if (c->quality < QUALITY_MAX)
            c->quality++;
        break;
    case '-': case '_':
        if (c->quality > QUALITY_MIN)
            c->quality--;
        else
            c->mode = MODE_LINES;
        break;
    case '\t': case 'n':  /* cycle: forest -> tree 0 -> tree 1 -> ... -> forest */
        V.focus = V.focus + 1 < c->tree_count ? V.focus + 1 : -1;
        camera_reset();
        break;
    case 'a':
        V.show_axes = !V.show_axes;
        break;
    case 'g':
        V.show_ground = !V.show_ground;
        break;
    case 'r':
        camera_reset();
        break;
    case 's':
        save_ppm("screenshot.ppm", glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        return;
    case 'q': case 27:
        exit(EXIT_SUCCESS);
    default:
        return;
    }
    invalidate();
}

static void on_special(int key, int x, int y)
{
    (void)x;
    (void)y;
    float step = V.camera.distance * 0.03f;
    float yaw = V.camera.yaw * (float)M_PI / 180.0f;

    switch (key) {
    case GLUT_KEY_LEFT:  V.camera.target[0] -= step * cosf(yaw); V.camera.target[2] += step * sinf(yaw); break;
    case GLUT_KEY_RIGHT: V.camera.target[0] += step * cosf(yaw); V.camera.target[2] -= step * sinf(yaw); break;
    case GLUT_KEY_UP:    V.camera.target[1] += step; break;
    case GLUT_KEY_DOWN:  V.camera.target[1] -= step; break;
    default: return;
    }
    glutPostRedisplay();
}

/* ------------------------------------------------------------------------- */
/* Setup                                                                     */
/* ------------------------------------------------------------------------- */

static void init_gl(void)
{
    glClearColor(0.70f, 0.80f, 0.90f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);
    const GLfloat ambient[] = { 0.35f, 0.35f, 0.38f, 1.0f };
    const GLfloat diffuse[] = { 0.85f, 0.82f, 0.75f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    V.quadric = gluNewQuadric();
    gluQuadricNormals(V.quadric, GLU_SMOOTH);
    gluQuadricTexture(V.quadric, GL_TRUE);

    const Image *bark = &V.cfg->bark;
    if (bark->rgb) {
        glGenTextures(1, &V.bark_texture);
        glBindTexture(GL_TEXTURE_2D, V.bark_texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bark->width, bark->height,
                          GL_RGB, GL_UNSIGNED_BYTE, bark->rgb);
    }
}

void viewer_run(int *argc, char **argv, ViewerConfig *cfg)
{
    V.cfg = cfg;
    V.focus = cfg->focus;
    V.show_ground = 1;
    V.scene_dirty = 1;
    V.drag_button = -1;

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(cfg->width, cfg->height);
    glutCreateWindow("Fractal trees");

    init_gl();
    camera_reset();
    update_title();

    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);
    glutKeyboardFunc(on_key);
    glutSpecialFunc(on_special);

    glutMainLoop();
}
