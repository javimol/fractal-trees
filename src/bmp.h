/*
 * bmp.h - Minimal loader for uncompressed 24-bit BMP images.
 *
 * Copyright (c) 2005-2006 Víctor Fernández-Carbajales Cañete and Javier Molina Vela
 * Copyright (c) 2026 Javier Molina Vela
 * SPDX-License-Identifier: MIT
 */
#ifndef BMP_H
#define BMP_H

typedef struct {
    int            width;
    int            height;
    unsigned char *rgb;  /* width*height*3 bytes, bottom row first (OpenGL order) */
} Image;

/* Returns 0 on success, -1 on error (message printed to stderr). */
int  bmp_load(const char *path, Image *img);
void image_free(Image *img);

#endif
