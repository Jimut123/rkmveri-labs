#ifndef Z_PNG_H_INCLUDED
#define Z_PNG_H_INCLUDED

#include <png.h>

struct image_st {
    unsigned int width;
    unsigned int height;
    unsigned int colortype;
    unsigned int bitdepth;
    unsigned char *pixels;
};

extern void png_read_file(char *, struct image_st *);
extern void png_write_file(char *, struct image_st *);
extern void png_free_image(struct image_st *);

#endif
