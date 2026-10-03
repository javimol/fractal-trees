/*
 * output.h - Writes generated trees as .fra branch lists or VRML 2.0 scenes.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include "generator.h"

#include <stdio.h>

/* Writes one line per straight piece, in the format described in
 * ../visualizer/src/tree.h. Returns the number of lines written. */
int write_fra(FILE *out, const Segment *root);

/* Writes a VRML 2.0 (.wrl) scene: a cylinder per piece, a sphere on each
 * joint and a cone on each branch tip. texture_url may be NULL. Returns the
 * number of pieces written. */
int write_vrml(FILE *out, const Segment *root, const char *name, const char *texture_url);

#endif
