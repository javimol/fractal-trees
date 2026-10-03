/*
 * rng.c - SplitMix64 generator behind the percentage-based interface in rng.h.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "rng.h"

static uint64_t next(Rng *rng)
{
    uint64_t z = (rng->state += 0x9E3779B97F4A7C15ull);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}

void rng_seed(Rng *rng, uint64_t seed)
{
    rng->state = seed;
}

int rng_percent(Rng *rng)
{
    /* Top 53 bits as a double in [0, 1), scaled to 0..100. */
    double u = (double)(next(rng) >> 11) * (1.0 / 9007199254740992.0);
    return (int)(u * 101.0);
}

int rng_chance(Rng *rng, float ratio)
{
    return rng_percent(rng) < ratio * 100.0f;
}

float rng_jitter(Rng *rng)
{
    return rng_percent(rng) > 50 ? -0.1f : 0.1f;
}
