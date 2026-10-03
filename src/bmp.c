/*
 * bmp.c - Minimal loader for uncompressed 24-bit BMP images.
 *
 * Copyright (c) 2005-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#include "bmp.h"

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t le32(const unsigned char *p)
{
    return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
}

static uint16_t le16(const unsigned char *p)
{
    return (uint16_t)(p[0] | p[1] << 8);
}

int bmp_load(const char *path, Image *img)
{
    memset(img, 0, sizeof *img);

    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "%s: %s\n", path, strerror(errno));
        return -1;
    }

    unsigned char header[54];
    if (fread(header, 1, sizeof header, f) != sizeof header || header[0] != 'B' || header[1] != 'M') {
        fprintf(stderr, "%s: not a BMP file\n", path);
        fclose(f);
        return -1;
    }

    uint32_t data_offset = le32(header + 10);
    int32_t  width       = (int32_t)le32(header + 18);
    int32_t  height      = (int32_t)le32(header + 22);
    uint16_t bpp         = le16(header + 28);
    uint32_t compression = le32(header + 30);

    if (bpp != 24 || compression != 0 || width <= 0 || height == 0) {
        fprintf(stderr, "%s: only uncompressed 24-bit BMPs are supported\n", path);
        fclose(f);
        return -1;
    }

    int top_down = height < 0;
    if (top_down)
        height = -height;

    size_t row_size = ((size_t)width * 3 + 3) & ~(size_t)3;  /* rows are 4-byte aligned */
    unsigned char *row = malloc(row_size);
    img->rgb = malloc((size_t)width * height * 3);
    if (!row || !img->rgb) {
        fprintf(stderr, "%s: out of memory\n", path);
        free(row);
        image_free(img);
        fclose(f);
        return -1;
    }

    fseek(f, (long)data_offset, SEEK_SET);
    for (int y = 0; y < height; y++) {
        if (fread(row, 1, row_size, f) != row_size) {
            fprintf(stderr, "%s: truncated file\n", path);
            free(row);
            image_free(img);
            fclose(f);
            return -1;
        }
        int dst_y = top_down ? height - 1 - y : y;  /* store bottom row first */
        unsigned char *dst = img->rgb + (size_t)dst_y * width * 3;
        for (int x = 0; x < width; x++) {          /* BGR -> RGB */
            dst[3 * x + 0] = row[3 * x + 2];
            dst[3 * x + 1] = row[3 * x + 1];
            dst[3 * x + 2] = row[3 * x + 0];
        }
    }

    free(row);
    fclose(f);
    img->width = width;
    img->height = height;
    return 0;
}

void image_free(Image *img)
{
    free(img->rgb);
    img->rgb = NULL;
    img->width = img->height = 0;
}
