/*
 * fractal-trees - 3D viewer for fractal tree models.
 *
 * Usage: fractal-trees [options] [FILE.fra | DIRECTORY]...
 * Run with --help for details.
 *
 * Copyright (c) 2004-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "bmp.h"
#include "tree.h"
#include "viewer.h"

#include <ctype.h>
#include <limits.h>
#include <getopt.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEFAULT_DATA_DIR "data/chopos"  /* searched as described in default_data_dir() */
#define MAX_PATH PATH_MAX

static void usage(const char *prog, FILE *out)
{
    fprintf(out,
        "Usage: %s [options] [FILE.fra | DIRECTORY]...\n"
        "\n"
        "Displays one or more fractal trees. A DIRECTORY loads every *.fra file in it\n"
        "(sorted naturally: Arbol2 before Arbol10) and uses bark.bmp, or else the first\n"
        "*.bmp in it, as the bark texture. Without arguments it loads the repository's\n"
        "'" DEFAULT_DATA_DIR "' folder.\n"
        "\n"
        "Options:\n"
        "  -m, --mode N         render mode: 0 lines, 1 cylinders, 2 cylinders + joints,\n"
        "                       3 textured (default 3)\n"
        "  -q, --quality N      tessellation level 1-10 (default 4)\n"
        "  -t, --texture FILE   bark texture, 24-bit BMP\n"
        "  -n, --tree N         show only tree N instead of the whole forest\n"
        "  -s, --seed N         forest layout seed (default 1)\n"
        "  -W, --size WxH       window size (default 900x900)\n"
        "  -o, --screenshot F   render one frame to F (PPM) and exit\n"
        "  -h, --help           show this help\n"
        "\n"
        "Controls:\n"
        "  left drag  orbit          0-3        render mode\n"
        "  right drag zoom           + / -      more / less detail\n"
        "  wheel      zoom           n or Tab   next tree / whole forest\n"
        "  middle drag pan           a / g      toggle axes / ground\n"
        "  arrows     pan            r          reset view\n"
        "  s          screenshot     q or Esc   quit\n",
        prog);
}

static int is_directory(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

static int file_exists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

/* Appends one loaded tree to the growing array. */
static int add_tree(const char *path, Tree **trees, int *count)
{
    Tree t;
    if (tree_load(path, &t) != 0)
        return -1;
    Tree *p = realloc(*trees, (size_t)(*count + 1) * sizeof *p);
    if (!p) {
        tree_free(&t);
        return -1;
    }
    *trees = p;
    (*trees)[(*count)++] = t;
    printf("Loaded %-28s %5zu branches\n", path, t.count);
    return 0;
}

/* Natural order: "Arbol2" sorts before "Arbol10". */
static int natural_cmp(const void *pa, const void *pb)
{
    const char *a = *(const char *const *)pa, *b = *(const char *const *)pb;
    while (*a && *b) {
        if (isdigit((unsigned char)*a) && isdigit((unsigned char)*b)) {
            char *ea, *eb;
            unsigned long na = strtoul(a, &ea, 10), nb = strtoul(b, &eb, 10);
            if (na != nb)
                return na < nb ? -1 : 1;
            a = ea;
            b = eb;
        } else {
            if (*a != *b)
                return (unsigned char)*a - (unsigned char)*b;
            a++;
            b++;
        }
    }
    return (unsigned char)*a - (unsigned char)*b;
}

/* Loads every *.fra in a directory (natural order). If no texture was chosen
 * yet, uses the directory's bark.bmp, or else its first *.bmp. */
static void add_directory(const char *dir, Tree **trees, int *count, char *texture, size_t texture_size)
{
    char pattern[MAX_PATH];
    snprintf(pattern, sizeof pattern, "%s/*.fra", dir);

    glob_t g;
    if (glob(pattern, 0, NULL, &g) != 0) {
        fprintf(stderr, "%s: no .fra files found\n", dir);
        return;
    }
    qsort(g.gl_pathv, g.gl_pathc, sizeof *g.gl_pathv, natural_cmp);
    for (size_t i = 0; i < g.gl_pathc; i++)
        add_tree(g.gl_pathv[i], trees, count);
    globfree(&g);

    if (texture[0] != '\0')
        return;
    char bark[MAX_PATH];
    snprintf(bark, sizeof bark, "%s/bark.bmp", dir);
    if (file_exists(bark)) {
        snprintf(texture, texture_size, "%s", bark);
        return;
    }
    snprintf(pattern, sizeof pattern, "%s/*.bmp", dir);
    if (glob(pattern, 0, NULL, &g) == 0) {
        qsort(g.gl_pathv, g.gl_pathc, sizeof *g.gl_pathv, natural_cmp);
        snprintf(texture, texture_size, "%s", g.gl_pathv[0]);
        globfree(&g);
    }
}

/* Parses a whole decimal integer within [lo, hi]. Returns 0 on success. */
static int parse_int(const char *s, int lo, int hi, int *out)
{
    char *end;
    long v = strtol(s, &end, 10);
    if (end == s || *end != '\0' || v < lo || v > hi)
        return -1;
    *out = (int)v;
    return 0;
}

/* Directory containing the running executable (Linux: /proc/self/exe,
 * elsewhere: the directory part of argv[0]). Empty string if unknown. */
static void executable_dir(const char *argv0, char *buf, size_t size)
{
    buf[0] = '\0';
#ifdef __linux__
    ssize_t n = readlink("/proc/self/exe", buf, size - 1);
    if (n > 0) {
        buf[n] = '\0';
        char *slash = strrchr(buf, '/');
        if (slash) {
            *slash = '\0';
            return;
        }
    }
#endif
    const char *slash = strrchr(argv0, '/');
    if (slash)
        snprintf(buf, size, "%.*s", (int)(slash - argv0), argv0);
    else
        buf[0] = '\0';
}

/* Finds data/chopos: first relative to the executable (which lives in
 * visualizer/, so ../data/chopos), then relative to the current directory. */
static const char *default_data_dir(const char *argv0, char *buf, size_t size)
{
    char exe_dir[MAX_PATH];
    executable_dir(argv0, exe_dir, sizeof exe_dir);

    const char *candidates[] = { "%s/../" DEFAULT_DATA_DIR, "%s/" DEFAULT_DATA_DIR };
    if (exe_dir[0] != '\0') {
        for (size_t i = 0; i < sizeof candidates / sizeof *candidates; i++) {
            char path[MAX_PATH];
            snprintf(path, sizeof path, candidates[i], exe_dir);
            if (is_directory(path)) {
                char resolved[PATH_MAX];
                snprintf(buf, size, "%s", realpath(path, resolved) ? resolved : path);
                return buf;
            }
        }
    }
    snprintf(buf, size, "%s", is_directory(DEFAULT_DATA_DIR) ? DEFAULT_DATA_DIR : "../" DEFAULT_DATA_DIR);
    return buf;
}

int main(int argc, char **argv)
{
    ViewerConfig cfg = {
        .mode = MODE_TEXTURED,
        .quality = 4,
        .width = 900,
        .height = 900,
        .seed = 1,
        .focus = -1,
    };
    char texture[MAX_PATH] = "";

    static const struct option options[] = {
        { "mode",       required_argument, NULL, 'm' },
        { "quality",    required_argument, NULL, 'q' },
        { "texture",    required_argument, NULL, 't' },
        { "tree",       required_argument, NULL, 'n' },
        { "seed",       required_argument, NULL, 's' },
        { "size",       required_argument, NULL, 'W' },
        { "screenshot", required_argument, NULL, 'o' },
        { "help",       no_argument,       NULL, 'h' },
        { NULL, 0, NULL, 0 }
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "m:q:t:n:s:W:o:h", options, NULL)) != -1) {
        switch (opt) {
        case 'm': {
            int mode;
            if (parse_int(optarg, 0, MODE_COUNT - 1, &mode) != 0) {
                fprintf(stderr, "Invalid mode: %s (expected 0-%d)\n", optarg, MODE_COUNT - 1);
                return EXIT_FAILURE;
            }
            cfg.mode = (RenderMode)mode;
            break;
        }
        case 'q':
            if (parse_int(optarg, 1, 10, &cfg.quality) != 0) {
                fprintf(stderr, "Invalid quality: %s (expected 1-10)\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 't': snprintf(texture, sizeof texture, "%s", optarg); break;
        case 'n':
            if (parse_int(optarg, 0, 1000000, &cfg.focus) != 0) {
                fprintf(stderr, "Invalid tree number: %s\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 's': {
            int seed;
            if (parse_int(optarg, 0, 2147483647, &seed) != 0) {
                fprintf(stderr, "Invalid seed: %s\n", optarg);
                return EXIT_FAILURE;
            }
            cfg.seed = (unsigned)seed;
            break;
        }
        case 'W':
            if (sscanf(optarg, "%dx%d", &cfg.width, &cfg.height) != 2 || cfg.width <= 0 || cfg.height <= 0) {
                fprintf(stderr, "Invalid size: %s (expected WxH)\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 'o': cfg.screenshot = optarg; break;
        case 'h': usage(argv[0], stdout); return EXIT_SUCCESS;
        default:  usage(argv[0], stderr); return EXIT_FAILURE;
        }
    }

    if (optind == argc) {
        char dir[MAX_PATH];
        add_directory(default_data_dir(argv[0], dir, sizeof dir), &cfg.trees, &cfg.tree_count, texture, sizeof texture);
    } else {
        for (int i = optind; i < argc; i++) {
            if (is_directory(argv[i]))
                add_directory(argv[i], &cfg.trees, &cfg.tree_count, texture, sizeof texture);
            else
                add_tree(argv[i], &cfg.trees, &cfg.tree_count);
        }
    }

    if (cfg.tree_count == 0) {
        fprintf(stderr, "No trees loaded.\n\n");
        usage(argv[0], stderr);
        return EXIT_FAILURE;
    }
    if (cfg.focus >= cfg.tree_count) {
        fprintf(stderr, "Tree %d does not exist (loaded %d trees)\n", cfg.focus, cfg.tree_count);
        return EXIT_FAILURE;
    }

    if (texture[0] != '\0' && bmp_load(texture, &cfg.bark) != 0)
        fprintf(stderr, "Continuing without texture.\n");
    if (cfg.mode == MODE_TEXTURED && !cfg.bark.rgb)
        cfg.mode = MODE_JOINTS;

    viewer_layout_forest(cfg.trees, cfg.tree_count, cfg.seed);
    viewer_run(&argc, argv, &cfg);  /* does not return */
    return EXIT_SUCCESS;
}
