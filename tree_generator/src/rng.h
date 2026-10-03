/*
 * rng.h - Small seeded random number generator.
 *
 * The 2006 program drew every random decision as an integer percentage from
 * 0 to 100 (rand() seeded with the clock). This keeps that interface but makes
 * the stream reproducible from a seed.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef RNG_H
#define RNG_H

#include <stdint.h>

typedef struct {
    uint64_t state;
} Rng;

void rng_seed(Rng *rng, uint64_t seed);

/* Uniform integer in [0, 100], both ends included. */
int rng_percent(Rng *rng);

/* True with probability ratio (0..1), tested as rng_percent() < ratio * 100. */
int rng_chance(Rng *rng, float ratio);

/* +0.1 or -0.1 with equal probability. The 2006 code called this randGauss();
 * a Gaussian was planned but the shipped version used this fixed +/-10%. */
float rng_jitter(Rng *rng);

#endif
