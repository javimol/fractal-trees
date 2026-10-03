/*
 * tree-generator - Grows random trees from a set of parameters and writes
 * them as .fra files for the visualizer, or as VRML scenes.
 *
 * Usage: tree-generator [options]
 * Run with --help for details.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "generator.h"
#include "output.h"
#include "params.h"
#include "rng.h"

#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

static void usage(const char *prog, FILE *out)
{
    fprintf(out,
        "Usage: %s [options]\n"
        "\n"
        "Grows random trees and writes them as .fra branch lists (for the visualizer)\n"
        "or as VRML 2.0 scenes. Without -p it uses the poplar parameters that made\n"
        "data/chopos.\n"
        "\n"
        "Options:\n"
        "  -p, --params FILE    read parameters from FILE (key = value lines)\n"
        "  -D, --set KEY=VALUE  override one parameter; can be repeated\n"
        "  -n, --count N        number of trees (default 1)\n"
        "  -s, --seed N         random seed (default: from the clock, printed to stderr)\n"
        "  -o, --output PATH    one tree: output file (default: standard output);\n"
        "                       several trees: a directory, filled with tree0.fra,\n"
        "                       tree1.fra, ... (created if needed)\n"
        "  -f, --format FMT     fra (default) or vrml\n"
        "  -t, --texture URL    bark image referenced by VRML output\n"
        "      --print-params   print the parameters in effect and exit\n"
        "  -h, --help           show this help\n"
        "\n"
        "Example:\n"
        "  %s -n 7 -o forest && ../visualizer/fractal-trees -t ../data/chopos/bark.bmp forest\n",
        prog, prog);
}

static int parse_int(const char *s, long min, long *out)
{
    char *end;
    errno = 0;
    long v = strtol(s, &end, 10);
    if (end == s || *end != '\0' || errno || v < min)
        return -1;
    *out = v;
    return 0;
}

static int ensure_directory(const char *path)
{
    if (mkdir(path, 0777) == 0 || errno == EEXIST) {
        struct stat st;
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
            return 0;
    }
    fprintf(stderr, "%s: can't create directory\n", path);
    return -1;
}

static int write_tree(const Segment *root, const char *path, int vrml,
                      const char *name, const char *texture)
{
    FILE *out = stdout;
    if (path && strcmp(path, "-") != 0) {
        out = fopen(path, "w");
        if (!out) {
            fprintf(stderr, "%s: %s\n", path, strerror(errno));
            return -1;
        }
    }

    int pieces = vrml ? write_vrml(out, root, name, texture) : write_fra(out, root);

    int status = 0;
    if (out != stdout) {
        if (fclose(out) != 0) {
            fprintf(stderr, "%s: %s\n", path, strerror(errno));
            status = -1;
        }
    } else if (fflush(out) != 0) {
        status = -1;
    }
    fprintf(stderr, "%s: %d branches\n", out == stdout ? "stdout" : path, pieces);
    return status;
}

int main(int argc, char **argv)
{
    Params params;
    params_default(&params);

    long count = 1;
    unsigned long long seed = (unsigned long long)time(NULL);
    const char *output = NULL;
    const char *texture = NULL;
    int vrml = 0;
    int print_params = 0;
    int status = 0;

    enum { OPT_PRINT_PARAMS = 256 };
    static const struct option long_opts[] = {
        { "params",       required_argument, NULL, 'p' },
        { "set",          required_argument, NULL, 'D' },
        { "count",        required_argument, NULL, 'n' },
        { "seed",         required_argument, NULL, 's' },
        { "output",       required_argument, NULL, 'o' },
        { "format",       required_argument, NULL, 'f' },
        { "texture",      required_argument, NULL, 't' },
        { "print-params", no_argument,       NULL, OPT_PRINT_PARAMS },
        { "help",         no_argument,       NULL, 'h' },
        { NULL, 0, NULL, 0 }
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "p:D:n:s:o:f:t:h", long_opts, NULL)) != -1) {
        switch (opt) {
        case 'p':
            if (params_load(&params, optarg) != 0)
                return EXIT_FAILURE;
            break;
        case 'D':
            if (params_set(&params, optarg) != 0)
                return EXIT_FAILURE;
            break;
        case 'n':
            if (parse_int(optarg, 1, &count) != 0) {
                fprintf(stderr, "Invalid count '%s'\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 's': {
            char *end;
            errno = 0;
            seed = strtoull(optarg, &end, 10);
            if (end == optarg || *end != '\0' || errno) {
                fprintf(stderr, "Invalid seed '%s'\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        }
        case 'o': output = optarg; break;
        case 'f':
            if (strcmp(optarg, "vrml") == 0)
                vrml = 1;
            else if (strcmp(optarg, "fra") != 0) {
                fprintf(stderr, "Unknown format '%s' (use fra or vrml)\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case 't': texture = optarg; break;
        case OPT_PRINT_PARAMS: print_params = 1; break;
        case 'h': usage(argv[0], stdout); return EXIT_SUCCESS;
        default:  usage(argv[0], stderr); return EXIT_FAILURE;
        }
    }
    if (optind < argc) {
        fprintf(stderr, "Unexpected argument '%s'\n", argv[optind]);
        usage(argv[0], stderr);
        return EXIT_FAILURE;
    }

    if (params_validate(&params) != 0)
        return EXIT_FAILURE;
    if (print_params) {
        params_write(&params, stdout);
        return EXIT_SUCCESS;
    }
    if (count > 1) {
        if (!output) {
            fprintf(stderr, "Several trees need an output directory (-o DIR)\n");
            return EXIT_FAILURE;
        }
        if (ensure_directory(output) != 0)
            return EXIT_FAILURE;
    }

    fprintf(stderr, "Seed %llu\n", seed);
    Rng rng;
    rng_seed(&rng, seed);

    for (long i = 0; i < count; i++) {
        Segment *root = tree_generate(&params, &rng);

        char name[32], path[PATH_MAX];
        snprintf(name, sizeof name, "tree%ld", i);
        const char *target = output;
        if (count > 1) {
            snprintf(path, sizeof path, "%s/%s.%s", output, name, vrml ? "wrl" : "fra");
            target = path;
        }
        if (write_tree(root, target, vrml, name, texture) != 0)
            status = EXIT_FAILURE;

        tree_free(root);
    }
    return status;
}
