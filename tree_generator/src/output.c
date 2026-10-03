/*
 * output.c - .fra and VRML writers.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "output.h"

#include <math.h>

#define RAD2DEG(a) ((a) * 180.0f / (float)M_PI)

/* Calls fn for each straight piece of the tree, depth first: a segment (or its
 * bent pieces), then its successor, then its branches. owner is the segment
 * the piece belongs to. */
typedef void (*PieceFn)(const Segment *piece, const Segment *owner, void *ctx);

static int for_each_piece(const Segment *s, PieceFn fn, void *ctx)
{
    int count = 0;
    for (const Segment *piece = s->bends ? s->bends : s; piece; piece = piece->next) {
        fn(piece, s, ctx);
        count++;
        if (!s->bends)
            break;
    }
    if (s->next)
        count += for_each_piece(s->next, fn, ctx);
    for (int i = 0; i < s->branch_count; i++)
        count += for_each_piece(s->branches[i], fn, ctx);
    return count;
}

static void fra_piece(const Segment *piece, const Segment *owner, void *ctx)
{
    (void)owner;
    /* Axis ends that never branched (the outermost twigs) come to a point. */
    float tip = (!piece->next && !piece->branched) ? 0.0f : piece->diameter_end;
    fprintf((FILE *)ctx, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
            piece->diameter_start, tip, piece->length,
            RAD2DEG(piece->polar), RAD2DEG(piece->azimuth),
            piece->start[0], piece->start[1], piece->start[2]);
}

int write_fra(FILE *out, const Segment *root)
{
    fprintf(out, "# D1\tD2\th\tFi\talfa\tr0x\tr0y\tr0z\n");
    return for_each_piece(root, fra_piece, out);
}

typedef struct {
    FILE       *out;
    const char *texture_url;
} VrmlContext;

static void vrml_shape(const VrmlContext *c, const char *indent, const char *geometry)
{
    fprintf(c->out,
            "%sShape {\n"
            "%s  appearance Appearance {\n"
            "%s    material Material { diffuseColor 0.5 0.5 0.5 emissiveColor 0.5 0.5 0.5 }\n",
            indent, indent, indent);
    if (c->texture_url)
        fprintf(c->out, "%s    texture ImageTexture { url \"%s\" }\n", indent, c->texture_url);
    fprintf(c->out,
            "%s  }\n"
            "%s  geometry %s\n"
            "%s}\n",
            indent, indent, geometry, indent);
}

/* The piece is built along +Y, tilted by its polar angle around X and turned
 * by its azimuth around Y, which matches the direction used by the generator. */
static void vrml_piece(const Segment *piece, const Segment *owner, void *ctx)
{
    const VrmlContext *c = ctx;
    float h = piece->length;
    float r = piece->diameter_start / 2.0f;
    int axis_end = !piece->next && !owner->next && owner->branch_count == 0;
    char geometry[128];

    fprintf(c->out,
            "      Transform {\n"
            "        translation %f %f %f\n"
            "        rotation 0 1 0 %f\n"
            "        children Transform {\n"
            "          rotation 1 0 0 %f\n"
            "          children [\n"
            "            Transform {\n"
            "              translation 0 %f 0\n"
            "              children\n",
            piece->start[0], piece->start[1], piece->start[2],
            piece->azimuth, piece->polar, h / 2.0f);
    snprintf(geometry, sizeof geometry, "Cylinder { height %f radius %f }", h, r);
    vrml_shape(c, "                ", geometry);
    fprintf(c->out, "            }\n");

    /* A cone closes the end of an axis; a sphere fills the joint otherwise. */
    if (axis_end) {
        fprintf(c->out, "            Transform {\n"
                        "              translation 0 %f 0\n"
                        "              children\n", h * 1.25f);
        snprintf(geometry, sizeof geometry, "Cone { bottomRadius %f height %f }", r, h / 2.0f);
    } else {
        fprintf(c->out, "            Transform {\n"
                        "              translation 0 %f 0\n"
                        "              children\n", h);
        snprintf(geometry, sizeof geometry, "Sphere { radius %f }", r);
    }
    vrml_shape(c, "                ", geometry);
    fprintf(c->out, "            }\n"
                    "          ]\n"
                    "        }\n"
                    "      }\n");
}

int write_vrml(FILE *out, const Segment *root, const char *name, const char *texture_url)
{
    VrmlContext c = { out, texture_url };
    fprintf(out,
            "#VRML V2.0 utf8\n"
            "DirectionalLight { direction 0.8 0.6 0 }\n"
            "Background { skyColor 0.5 0.5 0.5 }\n"
            "Viewpoint { position 0 0 400 fieldOfView 0.6 description \"Camera\" }\n"
            "DEF %s Transform {\n"
            "  scale 0.5 0.5 0.5\n"
            "  children [\n",
            name);
    int count = for_each_piece(root, vrml_piece, &c);
    fprintf(out, "  ]\n"
                 "}\n");
    return count;
}
