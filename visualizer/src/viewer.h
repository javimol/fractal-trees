/*
 * viewer.h - Interactive OpenGL/GLUT viewer for a forest of branch-list trees.
 *
 * Copyright (c) 2004-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef VIEWER_H
#define VIEWER_H

#include "bmp.h"
#include "tree.h"

typedef enum {
    MODE_LINES = 0,      /* one line segment per branch          */
    MODE_CYLINDERS,      /* tapered cylinders                    */
    MODE_JOINTS,         /* cylinders + spheres at branch tips   */
    MODE_TEXTURED,       /* cylinders + spheres with bark texture */
    MODE_COUNT
} RenderMode;

typedef struct {
    Tree       *trees;
    int         tree_count;
    Image       bark;            /* may be empty (rgb == NULL) */
    RenderMode  mode;
    int         quality;         /* 1..10, tessellation level */
    int         width, height;
    unsigned    seed;            /* forest layout seed */
    int         focus;           /* -1 = show the whole forest, else one tree */
    const char *screenshot;      /* if set: render one frame to this PPM file and exit */
} ViewerConfig;

/* Lays the trees out on the ground plane (sets Tree.offset). */
void viewer_layout_forest(Tree *trees, int count, unsigned seed);

/* Creates the window and enters the GLUT main loop. Does not return. */
void viewer_run(int *argc, char **argv, ViewerConfig *cfg);

#endif
