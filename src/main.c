/*
 * fractal-trees - 3D viewer for fractal tree models.
 *
 * Usage: fractal-trees [options] [FILE.fra | DIRECTORY]...
 * Run with --help for details.
 *
 * Copyright (c) 2005-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "bmp.h"
#include "tree.h"
#include "viewer.h"

#include <getopt.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DEFAULT_DATA_DIR "data"
#define MAX_PATH 1024

static void usage(const char *prog, FILE *out)
{
    fprintf(out,
        "Usage: %s [options] [FILE.fra | DIRECTORY]...\n"
        "\n"
        "Displays one or more fractal trees. A DIRECTORY loads every *.fra file in it\n"
        "(and its bark.bmp texture, if present). Default: '" DEFAULT_DATA_DIR "'.\n"
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

/* Loads every *.fra in a directory (sorted by name). */
static void add_directory(const char *dir, Tree **trees, int *count, char *texture, size_t texture_size)
{
    char pattern[MAX_PATH];
    snprintf(pattern, sizeof pattern, "%s/*.fra", dir);

    glob_t g;
    if (glob(pattern, 0, NULL, &g) != 0) {
        fprintf(stderr, "%s: no .fra files found\n", dir);
        return;
    }
    for (size_t i = 0; i < g.gl_pathc; i++)
        add_tree(g.gl_pathv[i], trees, count);
    globfree(&g);

    if (texture[0] == '\0') {
        char bark[MAX_PATH];
        snprintf(bark, sizeof bark, "%s/bark.bmp", dir);
        if (file_exists(bark))
            snprintf(texture, texture_size, "%s", bark);
    }
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
        case 'm':
            cfg.mode = (RenderMode)atoi(optarg);
            if (cfg.mode < 0 || cfg.mode >= MODE_COUNT) {
                fprintf(stderr, "Invalid mode: %s\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 'q':
            cfg.quality = atoi(optarg);
            if (cfg.quality < 1) cfg.quality = 1;
            if (cfg.quality > 10) cfg.quality = 10;
            break;
        case 't': snprintf(texture, sizeof texture, "%s", optarg); break;
        case 'n': cfg.focus = atoi(optarg); break;
        case 's': cfg.seed = (unsigned)strtoul(optarg, NULL, 10); break;
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
        add_directory(DEFAULT_DATA_DIR, &cfg.trees, &cfg.tree_count, texture, sizeof texture);
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
