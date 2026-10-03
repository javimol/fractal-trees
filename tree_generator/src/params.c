/*
 * params.c - Parameter defaults, file parsing and per-tree size variation.
 *
 * Copyright (c) 2006 Víctor Fernández-Carbajales Cañete
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "params.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DEG2RAD(a) ((a) * (float)M_PI / 180.0f)
#define RAD2DEG(a) ((a) * 180.0f / (float)M_PI)

typedef enum { NUMBER, INTEGER, PERCENT, DEGREES } Unit;

typedef struct {
    const char *key;
    size_t      offset;
    Unit        unit;
    const char *help;
} Field;

#define FIELD(name, unit, help) { #name, offsetof(Params, name), unit, help }

static const Field fields[] = {
    FIELD(max_height,            NUMBER,  "height cap"),
    FIELD(growth_rate,           NUMBER,  "height gained per year"),
    FIELD(age,                   NUMBER,  "age in months; height = min(age / 12 * growth_rate, max_height)"),
    FIELD(trunk_ratio,           PERCENT, "% of the height taken by the first trunk segment"),
    FIELD(segment_ratio,         PERCENT, "% length of each segment relative to the one before"),
    FIELD(base_ratio,            PERCENT, "% base diameter relative to the height"),
    FIELD(taper,                 PERCENT, "% diameter lost along each segment"),
    FIELD(branch_ratio,          PERCENT, "% branch length relative to its parent segment"),
    FIELD(branch_diameter_ratio, PERCENT, "% branch base diameter relative to the parent tip"),
    FIELD(cone,                  DEGREES, "polar angle of first-generation branches"),
    FIELD(cone_increment,        DEGREES, "cone widening: level n adds cone_increment * (1/2 + ... + 1/(n+1))"),
    FIELD(min_azimuth,           DEGREES, "azimuth range where branches grow"),
    FIELD(max_azimuth,           DEGREES, ""),
    FIELD(generations,           INTEGER, "branching levels, also the maximum segments per axis"),
    FIELD(frondage,              PERCENT, "100/frondage sections around a segment, each branching with (100 - frondage)% chance"),
    FIELD(stop_probability,      PERCENT, "% chance that an axis stops instead of growing a new segment"),
    FIELD(deviousness,           PERCENT, "% chance a segment is bent; bent ones split into 1 + 100/(100 - deviousness) pieces"),
    FIELD(bend_angle,            DEGREES, "maximum polar angle of each bent piece"),
    FIELD(bend_arc,              DEGREES, "azimuth turn between pieces, in [-bend_arc/2, bend_arc/2]"),
    FIELD(variability,           PERCENT, "% chance and maximum size of random changes to lengths, angles and diameters"),
};

#define FIELD_COUNT (sizeof fields / sizeof fields[0])

void params_default(Params *p)
{
    /* Poplar forest from the 2006 slides ("Bosque de chopos"). */
    *p = (Params){
        .max_height            = 900,
        .growth_rate           = 25,
        .age                   = 100,
        .trunk_ratio           = 0.30f,
        .segment_ratio         = 0.80f,
        .base_ratio            = 0.05f,
        .taper                 = 0.05f,
        .branch_ratio          = 0.60f,
        .branch_diameter_ratio = 0.35f,
        .cone                  = DEG2RAD(50),
        .cone_increment        = DEG2RAD(15),
        .min_azimuth           = DEG2RAD(0),
        .max_azimuth           = DEG2RAD(360),
        .generations           = 3,
        .frondage              = 0.25f,
        .stop_probability      = 0.25f,
        .deviousness           = 0.50f,
        .bend_angle            = DEG2RAD(60),
        .bend_arc              = DEG2RAD(45),
        .variability           = 0.35f,
    };
}

static const Field *find_field(const char *key)
{
    for (size_t i = 0; i < FIELD_COUNT; i++)
        if (strcmp(fields[i].key, key) == 0)
            return &fields[i];
    return NULL;
}

static char *trim(char *s)
{
    while (isspace((unsigned char)*s))
        s++;
    char *end = s + strlen(s);
    while (end > s && isspace((unsigned char)end[-1]))
        *--end = '\0';
    return s;
}

/* Parses "key = value" (or "key=value") into p. where is used in messages. */
static int set_from_line(Params *p, char *line, const char *where)
{
    char *eq = strchr(line, '=');
    if (!eq) {
        fprintf(stderr, "%s: expected key = value\n", where);
        return -1;
    }
    *eq = '\0';
    char *key = trim(line);
    char *value = trim(eq + 1);

    const Field *f = find_field(key);
    if (!f) {
        fprintf(stderr, "%s: unknown parameter '%s'\n", where, key);
        return -1;
    }

    char *end;
    errno = 0;
    double v = strtod(value, &end);
    if (end == value || *trim(end) != '\0' || errno) {
        fprintf(stderr, "%s: '%s' is not a number\n", where, value);
        return -1;
    }

    void *dst = (char *)p + f->offset;
    switch (f->unit) {
    case INTEGER:
        if (v != floor(v)) {
            fprintf(stderr, "%s: %s must be a whole number\n", where, key);
            return -1;
        }
        *(int *)dst = (int)v;
        break;
    case PERCENT: *(float *)dst = (float)(v / 100.0); break;
    case DEGREES: *(float *)dst = DEG2RAD((float)v);  break;
    case NUMBER:  *(float *)dst = (float)v;           break;
    }
    return 0;
}

int params_set(Params *p, const char *assignment)
{
    char buf[256];
    snprintf(buf, sizeof buf, "%s", assignment);
    return set_from_line(p, buf, assignment);
}

int params_load(Params *p, const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        return -1;
    }

    char line[256], where[512];
    int line_no = 0, status = 0;
    while (fgets(line, sizeof line, f)) {
        line_no++;
        char *hash = strchr(line, '#');
        if (hash)
            *hash = '\0';
        char *s = trim(line);
        if (*s == '\0')
            continue;
        snprintf(where, sizeof where, "%s:%d", path, line_no);
        if (set_from_line(p, s, where) != 0)
            status = -1;
    }
    fclose(f);
    return status;
}

int params_validate(const Params *p)
{
    struct { int ok; const char *msg; } checks[] = {
        { p->max_height > 0,                        "max_height must be positive" },
        { p->growth_rate > 0,                       "growth_rate must be positive" },
        { p->age > 0,                               "age must be positive" },
        { p->generations >= 0,                      "generations can't be negative" },
        { p->frondage > 0 && p->frondage <= 1,      "frondage must be in (0, 100]" },
        { p->deviousness >= 0 && p->deviousness < 1, "deviousness must be in [0, 100)" },
        { p->min_azimuth >= 0 && p->min_azimuth < p->max_azimuth &&
          p->max_azimuth <= DEG2RAD(360) + 1e-4f,   "need 0 <= min_azimuth < max_azimuth <= 360" },
        { p->variability >= 0 && p->variability <= 1, "variability must be in [0, 100]" },
    };
    int status = 0;
    for (size_t i = 0; i < sizeof checks / sizeof checks[0]; i++) {
        if (!checks[i].ok) {
            fprintf(stderr, "Invalid parameters: %s\n", checks[i].msg);
            status = -1;
        }
    }
    return status;
}

void params_write(const Params *p, FILE *out)
{
    for (size_t i = 0; i < FIELD_COUNT; i++) {
        const Field *f = &fields[i];
        const void *src = (const char *)p + f->offset;
        double v = 0;
        switch (f->unit) {
        case INTEGER: v = *(const int *)src;                   break;
        case PERCENT: v = *(const float *)src * 100.0;         break;
        case DEGREES: v = RAD2DEG(*(const float *)src);        break;
        case NUMBER:  v = *(const float *)src;                 break;
        }
        if (f->help[0])
            fprintf(out, "%-22s = %-8g # %s\n", f->key, v, f->help);
        else
            fprintf(out, "%-22s = %g\n", f->key, v);
    }
}

/* With probability variability, changes value by up to +/-variability.
 * The change and its size come from the same draw, as in the 2006 code. */
static float vary_size(float value, float variability, Rng *rng)
{
    int amount = rng_percent(rng);
    if (amount > variability * 100.0f)
        return value;
    float delta = value * (float)amount / 100.0f;
    return rng_percent(rng) <= 50 ? value + delta : value - delta;
}

static void set_height(TreeSize *s, const Params *p, float height)
{
    s->height        = height;
    s->trunk_height  = height * p->trunk_ratio;
    s->crown_height  = height * (1.0f - p->trunk_ratio);
    s->base_diameter = height * p->base_ratio;
}

void params_tree_size(const Params *p, Rng *rng, TreeSize *s)
{
    float height = p->age / 12.0f * p->growth_rate;
    if (height > p->max_height)
        height = p->max_height;
    set_height(s, p, height);

    float v = p->variability;
    set_height(s, p, vary_size(s->height, v, rng));

    /* Trunk and crown share the height. A change that would leave either one
     * with no length is dropped (the 2006 code could grow the trunk downwards). */
    float trunk = vary_size(s->trunk_height, v, rng);
    if (trunk > 0 && trunk < s->height) {
        s->trunk_height = trunk;
        s->crown_height = s->height - trunk;
    }

    float crown = vary_size(s->crown_height, v, rng);
    if (crown > 0 && crown < s->height) {
        s->crown_height = crown;
        s->trunk_height = s->height - crown;
    }

    s->base_diameter = vary_size(s->base_diameter, v, rng);
}
