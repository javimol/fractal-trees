/*
 * generator.h - Grows a tree as a structure of tapered segments.
 *
 * Each axis (the trunk or a branch) is a chain of segments linked by `next`.
 * Every segment can sprout branches, which start new axes one generation
 * higher. A segment can also be "bent": then it's drawn as a chain of shorter
 * pieces (`bends`) with random directions instead of one straight cylinder.
 *
 * Growth runs in steps. A segment is born, lives for one step, during which it
 * grows its successor and its branches, and is then dead.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef GENERATOR_H
#define GENERATOR_H

#include "params.h"
#include "rng.h"

typedef enum { BORN, ALIVE, DEAD } SegmentState;

typedef struct Segment {
    float start[3];
    float end[3];
    float diameter_start;
    float diameter_end;
    float azimuth;              /* around +Y, radians, 0 = +Z, pi/2 = +X */
    float polar;                /* from +Y, radians                      */
    float length;

    SegmentState state;
    int generation;             /* 0 for the trunk, +1 per branching level */
    int age;                    /* segments between this one and the root  */

    struct Segment *parent;     /* previous segment, or the one branched from */
    struct Segment *next;       /* successor on the same axis                 */
    struct Segment **branches;
    int branch_count;
    int branched;               /* branching was attempted (even if none grew) */

    struct Segment *bends;      /* first piece of a bent segment, or NULL */
} Segment;

/* Grows a tree. Returns the root segment, or NULL if out of memory. */
Segment *tree_generate(const Params *p, Rng *rng);

void tree_free(Segment *root);

#endif
