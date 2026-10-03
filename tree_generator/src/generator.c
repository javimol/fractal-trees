/*
 * generator.c - Tree growth. See generator.h for the model.
 *
 * Every random decision follows the 2006 program: draw a percentage and
 * compare it with a parameter, and nudge most lengths, angles and diameters
 * by +/-10% at the end (rng_jitter).
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "generator.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEG2RAD(a) ((a) * (float)M_PI / 180.0f)

typedef struct {
    const Params *p;
    TreeSize      size;
    Rng          *rng;
} Grower;

static void *xcalloc(size_t n, size_t size)
{
    void *ptr = calloc(n ? n : 1, size);
    if (!ptr) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

static Segment *new_segment(void)
{
    return xcalloc(1, sizeof(Segment));
}

/* Point at distance d from start along the direction (polar, azimuth). */
static void advance(const float start[3], float polar, float azimuth, float d, float out[3])
{
    out[0] = start[0] + d * sinf(polar) * sinf(azimuth);
    out[1] = start[1] + d * cosf(polar);
    out[2] = start[2] + d * sinf(polar) * cosf(azimuth);
}

static void set_end(Segment *s)
{
    advance(s->start, s->polar, s->azimuth, s->length, s->end);
}

static float jitter(Grower *g, float value)
{
    return value + value * rng_jitter(g->rng);
}

/* With probability variability, scales value up or down by the drawn percentage. */
static float vary(Grower *g, float value)
{
    int amount = rng_percent(g->rng);
    int up = rng_percent(g->rng) >= 50;
    if (amount >= g->p->variability * 100.0f)
        return value;
    float delta = value * (float)amount / 100.0f;
    return up ? value + delta : value - delta;
}

/* Rounds x >= 0 to the nearest integer, halves up. */
static int round_count(float x)
{
    return (int)(x + 0.5f);
}

/* Last piece of a bent segment, or the segment itself. Successors and
 * tip branches start at its end. */
static const Segment *tip_piece(const Segment *s)
{
    if (!s->bends)
        return s;
    const Segment *piece = s->bends;
    while (piece->next)
        piece = piece->next;
    return piece;
}

/* Point at distance d from the start of s, following its pieces if bent. */
static void point_along(const Segment *s, float d, float out[3])
{
    const Segment *piece = s->bends ? s->bends : s;
    while (d > piece->length && piece->next && s->bends) {
        d -= piece->length;
        piece = piece->next;
    }
    advance(piece->start, piece->polar, piece->azimuth, d, out);
}

static int compare_int(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

/* Splits s into pieces: cut at random distinct percentages of its length, then
 * every piece after the first gets a random polar angle up to bend_angle and
 * turns its azimuth by up to bend_arc / 2 either way. The diameter tapers
 * linearly along the pieces. The first piece keeps the direction of s, jittered
 * unless s is the root. */
static Segment *make_bends(Grower *g, const Segment *s, int is_root)
{
    const Params *p = g->p;
    int cut_count = round_count(1.0f / (1.0f - p->deviousness));
    if (cut_count > 99)
        cut_count = 99;

    int cuts[100];
    for (int i = 0; i < cut_count; i++) {
        int c, duplicate;
        do {
            c = rng_percent(g->rng);
            if (c == 0)   c = 1;
            if (c == 100) c = 99;
            duplicate = 0;
            for (int j = 0; j < i; j++)
                duplicate |= cuts[j] == c;
        } while (duplicate);
        cuts[i] = c;
    }
    qsort(cuts, (size_t)cut_count, sizeof cuts[0], compare_int);
    cuts[cut_count] = 100;

    float taper_per_unit = (s->diameter_end - s->diameter_start) / s->length;
    float diameter = s->diameter_start;

    Segment *first = NULL, *prev = NULL;
    for (int i = 0; i <= cut_count; i++) {
        Segment *piece = new_segment();
        int from = i == 0 ? 0 : cuts[i - 1];
        piece->length = (float)(cuts[i] - from) / 100.0f * s->length;

        if (i == 0) {
            memcpy(piece->start, s->start, sizeof piece->start);
            piece->azimuth = is_root ? s->azimuth : jitter(g, s->azimuth);
            piece->polar   = is_root ? s->polar   : jitter(g, s->polar);
        } else {
            memcpy(piece->start, prev->end, sizeof piece->start);
            piece->polar = (float)rng_percent(g->rng) * p->bend_angle / 100.0f;
            piece->azimuth = prev->azimuth
                           + (float)rng_percent(g->rng) * p->bend_arc / 100.0f
                           - p->bend_arc / 2.0f;
        }
        set_end(piece);

        piece->diameter_start = diameter;
        diameter += taper_per_unit * piece->length;
        piece->diameter_end = diameter;

        piece->state = DEAD;
        piece->generation = s->generation;
        piece->age = s->age;
        piece->branched = 1;
        piece->parent = prev;

        if (prev)
            prev->next = piece;
        else
            first = piece;
        prev = piece;
    }
    return first;
}

static void maybe_bend(Grower *g, Segment *s, int is_root)
{
    if (rng_chance(g->rng, g->p->deviousness))
        s->bends = make_bends(g, s, is_root);
}

/* First trunk segment, from the origin. With probability variability it
 * leans: random azimuth, polar angle up to 67.5 degrees, both scaled by the
 * same draw. */
static Segment *grow_root(Grower *g)
{
    const Params *p = g->p;
    Segment *s = new_segment();

    s->diameter_start = jitter(g, g->size.base_diameter);
    s->diameter_end   = jitter(g, g->size.base_diameter * (1.0f - p->taper));

    int lean = rng_percent(g->rng);
    int azimuth = rng_percent(g->rng);
    int polar = rng_percent(g->rng);
    if (lean <= p->variability * 100.0f) {
        s->azimuth = DEG2RAD(azimuth * (lean / 100.0f) * 3.6f);
        s->polar   = DEG2RAD(polar * (lean / 100.0f) * 0.675f);
    }
    s->azimuth = jitter(g, s->azimuth);
    s->polar   = jitter(g, s->polar);

    s->length = jitter(g, g->size.trunk_height);
    set_end(s);

    s->state = BORN;
    maybe_bend(g, s, 1);
    return s;
}

/* Continues the axis of s with a shorter, thinner segment in roughly the same
 * direction, unless the axis is already `generations` segments long or it
 * stops at random. A trunk segment that ends above the target height is born
 * dead and removed later by prune(). */
static void grow_successor(Grower *g, Segment *s)
{
    const Params *p = g->p;
    if (s->age >= p->generations)
        return;
    if (rng_chance(g->rng, p->stop_probability))
        return;

    const Segment *tip = tip_piece(s);
    Segment *n = new_segment();
    memcpy(n->start, tip->end, sizeof n->start);
    n->diameter_start = s->diameter_end;

    n->azimuth = jitter(g, vary(g, tip->azimuth));
    n->polar   = jitter(g, vary(g, tip->polar));

    n->generation = s->generation;
    n->age = s->age + 1;

    n->length = jitter(g, vary(g, s->length * p->segment_ratio));
    n->diameter_end = jitter(g, vary(g, n->diameter_start * (1.0f - p->taper)));
    set_end(n);

    n->parent = s;
    n->state = BORN;
    if (n->generation == 0 && n->end[1] > g->size.height)
        n->state = DEAD;

    maybe_bend(g, n, 0);
    s->next = n;
}

/* Grows the branches of s. The azimuth range is split into round(1/frondage)
 * sections, starting at a random offset; each section holds a branch with
 * probability 1 - frondage. A branch's polar angle is a random fraction of the
 * cone for its generation, and it starts either at the tip of s or, with
 * probability variability, part way along it. */
static void grow_branches(Grower *g, Segment *s)
{
    const Params *p = g->p;
    if (s->generation >= p->generations)
        return;
    s->branched = 1;

    float cone = p->cone;
    for (int i = 0; i < s->generation; i++)
        cone += p->cone_increment / (float)(i + 2);

    int sections = round_count(1.0f / p->frondage);
    int *has_branch = xcalloc((size_t)sections, sizeof(int));
    int count = 0;
    for (int i = 0; i < sections; i++) {
        has_branch[i] = rng_percent(g->rng) / 100.0f <= 1.0f - p->frondage;
        count += has_branch[i];
    }

    float range = p->max_azimuth - p->min_azimuth;
    float step = range / (float)sections;
    float section_start = (float)rng_percent(g->rng) * range / 100.0f + p->min_azimuth;

    s->branches = xcalloc((size_t)count, sizeof(Segment *));
    s->branch_count = 0;

    for (int i = 0; i < sections; i++) {
        float section_end = section_start + step;

        if (has_branch[i]) {
            Segment *b = new_segment();

            b->azimuth = (float)rng_percent(g->rng) * step / 100.0f + section_start;
            if (b->azimuth >= p->max_azimuth)
                b->azimuth -= p->max_azimuth;
            b->azimuth = jitter(g, b->azimuth);

            /* The cone itself drifts from one branch to the next. */
            int fraction = rng_percent(g->rng);
            int drift = rng_percent(g->rng);
            if (fraction < p->variability * 100.0f)
                cone += (drift < 50 ? -cone : cone) * (float)drift / 100.0f;
            b->polar = jitter(g, (float)fraction * cone / 100.0f);

            int along = rng_percent(g->rng);
            if (along <= p->variability * 100.0f)
                point_along(s, s->length * (1.0f - (float)along / 100.0f), b->start);
            else
                memcpy(b->start, tip_piece(s)->end, sizeof b->start);

            b->generation = s->generation + 1;
            b->age = s->age + 1;

            b->length = jitter(g, vary(g, s->length * p->branch_ratio + s->diameter_end / 2.0f));

            float diameter = s->diameter_end * p->branch_diameter_ratio;
            b->diameter_end = vary(g, diameter * (1.0f - p->taper));
            b->diameter_start = jitter(g, diameter);
            b->diameter_end = jitter(g, b->diameter_end);
            set_end(b);

            b->parent = s;
            b->state = BORN;
            maybe_bend(g, b, 0);
            s->branches[s->branch_count++] = b;
        }

        if (section_end >= p->max_azimuth)
            section_end -= p->max_azimuth;
        section_start = section_end;
    }
    free(has_branch);
}

/* Born segments become alive and alive ones die. */
static void advance_states(Segment *s)
{
    if (s->next)
        advance_states(s->next);
    for (int i = 0; i < s->branch_count; i++)
        advance_states(s->branches[i]);

    if (s->state == ALIVE)
        s->state = DEAD;
    else if (s->state == BORN)
        s->state = ALIVE;
}

typedef struct {
    Segment **items;
    size_t    count, capacity;
} SegmentList;

static void collect_alive(Segment *s, SegmentList *list)
{
    if (s->next)
        collect_alive(s->next, list);
    for (int i = 0; i < s->branch_count; i++)
        collect_alive(s->branches[i], list);

    if (s->state == ALIVE) {
        if (list->count == list->capacity) {
            list->capacity = list->capacity ? list->capacity * 2 : 64;
            list->items = realloc(list->items, list->capacity * sizeof *list->items);
            if (!list->items) {
                fprintf(stderr, "Out of memory\n");
                exit(EXIT_FAILURE);
            }
        }
        list->items[list->count++] = s;
    }
}

/* Removes trunk segments that never got to branch (those born dead above the
 * target height) and sets the tip diameter of each axis end with branches to
 * the widest branch starting there, so they join smoothly. */
static void prune(Segment *s)
{
    if (s->next)
        prune(s->next);
    for (int i = 0; i < s->branch_count; i++)
        prune(s->branches[i]);

    if (!s->branched && s->generation == 0 && s->parent) {
        s->parent->next = NULL;
        tree_free(s);
        return;
    }

    if (!s->next && s->branch_count > 0) {
        Segment *tip = (Segment *)tip_piece(s);
        float widest = 0.0f;
        for (int i = 0; i < s->branch_count; i++) {
            const Segment *b = s->branches[i];
            if (memcmp(b->start, tip->end, sizeof b->start) == 0 && b->diameter_start > widest)
                widest = b->diameter_start;
        }
        s->diameter_end = widest;
        tip->diameter_end = widest;
    }
}

Segment *tree_generate(const Params *p, Rng *rng)
{
    Grower g = { .p = p, .rng = rng };
    params_tree_size(p, rng, &g.size);

    Segment *root = grow_root(&g);

    SegmentList alive = { 0 };
    for (;;) {
        advance_states(root);
        alive.count = 0;
        collect_alive(root, &alive);
        if (alive.count == 0)
            break;
        for (size_t i = 0; i < alive.count; i++) {
            grow_successor(&g, alive.items[i]);
            grow_branches(&g, alive.items[i]);
        }
    }
    free(alive.items);

    prune(root);
    return root;
}

void tree_free(Segment *s)
{
    if (!s)
        return;
    tree_free(s->next);
    for (int i = 0; i < s->branch_count; i++)
        tree_free(s->branches[i]);
    free(s->branches);
    tree_free(s->bends);
    free(s);
}
