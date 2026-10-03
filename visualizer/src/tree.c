/*
 * tree.c - .fra loader. See tree.h for the file format.
 *
 * Copyright (c) 2004-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "tree.h"

#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEG2RAD(a) ((a) * (float)M_PI / 180.0f)

void branch_tip(const Branch *b, float out[3])
{
    for (int k = 0; k < 3; k++)
        out[k] = b->base[k] + b->length * b->dir[k];
}

static int is_comment_or_blank(const char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return *line == '\0' || *line == '\n' || *line == '\r' || *line == '#' ||
           (line[0] == '/' && line[1] == '/');
}

static void update_bounds(Tree *t, const float p[3])
{
    for (int k = 0; k < 3; k++) {
        if (p[k] < t->bbox_min[k]) t->bbox_min[k] = p[k];
        if (p[k] > t->bbox_max[k]) t->bbox_max[k] = p[k];
    }
}

int tree_load(const char *path, Tree *tree)
{
    memset(tree, 0, sizeof *tree);
    for (int k = 0; k < 3; k++) {
        tree->bbox_min[k] = FLT_MAX;
        tree->bbox_max[k] = -FLT_MAX;
    }

    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        return -1;
    }

    size_t capacity = 0;
    char line[512];
    int line_no = 0;

    while (fgets(line, sizeof line, f)) {
        line_no++;
        if (is_comment_or_blank(line))
            continue;

        float d1, d2, h, fi, alfa, x, y, z;
        if (sscanf(line, "%f %f %f %f %f %f %f %f",
                   &d1, &d2, &h, &fi, &alfa, &x, &y, &z) != 8) {
            fprintf(stderr, "%s:%d: expected 8 numbers, skipping line\n", path, line_no);
            continue;
        }

        if (tree->count == capacity) {
            size_t new_cap = capacity ? capacity * 2 : 256;
            Branch *p = realloc(tree->branches, new_cap * sizeof *p);
            if (!p) {
                fprintf(stderr, "%s: out of memory\n", path);
                fclose(f);
                tree_free(tree);
                return -1;
            }
            tree->branches = p;
            capacity = new_cap;
        }

        Branch *b = &tree->branches[tree->count++];
        b->base[0] = x;
        b->base[1] = y;
        b->base[2] = z;
        b->dir[0] = sinf(DEG2RAD(fi)) * sinf(DEG2RAD(alfa));
        b->dir[1] = cosf(DEG2RAD(fi));
        b->dir[2] = sinf(DEG2RAD(fi)) * cosf(DEG2RAD(alfa));
        b->length = h;
        b->radius_base = d1 * 0.5f;
        b->radius_tip = d2 * 0.5f;

        float tip[3];
        branch_tip(b, tip);
        update_bounds(tree, b->base);
        update_bounds(tree, tip);
    }
    fclose(f);

    if (tree->count == 0) {
        fprintf(stderr, "%s: no branches found\n", path);
        tree_free(tree);
        return -1;
    }
    return 0;
}

void tree_free(Tree *tree)
{
    free(tree->branches);
    tree->branches = NULL;
    tree->count = 0;
}
