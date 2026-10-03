/*
 * params.h - Tree generation parameters.
 *
 * Parameters are read from a text file of "key = value" lines (see
 * presets/poplar.txt). Percentages are given as 0-100 and angles in degrees,
 * as in the 2006 program's dialog. Internally they are stored as 0-1 ratios
 * and radians.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef PARAMS_H
#define PARAMS_H

#include "rng.h"

#include <stdio.h>

typedef struct {
    /* Size */
    float max_height;            /* height cap                                     */
    float growth_rate;           /* height gained per year                         */
    float age;                   /* in months                                      */
    float trunk_ratio;           /* first trunk segment / total height             */
    float segment_ratio;         /* length of a segment / length of the previous   */
    float base_ratio;            /* base diameter / total height                   */
    float taper;                 /* diameter lost along each segment               */
    float branch_ratio;          /* branch length / parent segment length          */
    float branch_diameter_ratio; /* branch base diameter / parent tip diameter     */

    /* Branching */
    float cone;                  /* polar angle of first-generation branches       */
    float cone_increment;        /* added to the cone, divided by 2, 3... per level */
    float min_azimuth;           /* azimuth range where branches can grow          */
    float max_azimuth;
    int   generations;           /* branching levels, and segments per axis        */
    float frondage;              /* sets the branching sections and probability    */
    float stop_probability;      /* chance that an axis does not grow a new segment */

    /* Crookedness: segments split into bent sub-segments */
    float deviousness;           /* chance a segment is bent; also sets its pieces */
    float bend_angle;            /* maximum polar angle of each piece              */
    float bend_arc;              /* azimuth turn between pieces, centred on 0      */

    /* Randomness */
    float variability;           /* chance and size of random parameter changes    */
} Params;

/* Values derived from the parameters, varied for each tree. */
typedef struct {
    float height;                /* target height; the trunk stops above it */
    float trunk_height;          /* length of the first trunk segment       */
    float crown_height;          /* height - trunk_height                    */
    float base_diameter;
} TreeSize;

/* Fills in the poplar parameters used for data/chopos. */
void params_default(Params *p);

/* Reads "key = value" lines over the current values. Returns 0 on success,
 * -1 on error (message printed to stderr). */
int params_load(Params *p, const char *path);

/* Sets one parameter from a "key=value" string. Returns 0 on success. */
int params_set(Params *p, const char *assignment);

/* Checks ranges. Returns 0 if usable, -1 otherwise (message to stderr). */
int params_validate(const Params *p);

/* Writes the parameters in the format params_load() reads. */
void params_write(const Params *p, FILE *out);

/* Computes the tree size and applies random variation to it. */
void params_tree_size(const Params *p, Rng *rng, TreeSize *size);

#endif
