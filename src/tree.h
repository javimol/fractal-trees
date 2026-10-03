/*
 * tree.h - Branch-list tree model and .fra file loader.
 *
 * A .fra file describes one tree as a list of branches, one per line:
 *
 *     D1  D2  h  Fi  alfa  r0x  r0y  r0z
 *
 *   D1, D2   diameter at the base and at the tip of the branch
 *   h        branch length
 *   Fi       polar angle from the vertical (+Y), in degrees
 *   alfa     azimuth around the vertical, in degrees (0 = +Z, 90 = +X)
 *   r0*      position of the centre of the branch base
 *
 * Lines that are empty or start with '#' or '//' are ignored.
 *
 * Copyright (c) 2005-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef TREE_H
#define TREE_H

#include <stddef.h>

typedef struct {
    float base[3];      /* centre of the base                 */
    float dir[3];       /* unit growth direction              */
    float length;
    float radius_base;
    float radius_tip;
} Branch;

typedef struct {
    Branch *branches;
    size_t  count;
    float   bbox_min[3];  /* axis-aligned bounds of all branch end points */
    float   bbox_max[3];
    float   offset[3];    /* placement of the tree in the scene           */
} Tree;

/* Loads a tree from a .fra file. Returns 0 on success, -1 on error
 * (an error message is printed to stderr). */
int  tree_load(const char *path, Tree *tree);
void tree_free(Tree *tree);

/* Tip position of a branch. */
void branch_tip(const Branch *b, float out[3]);

#endif
