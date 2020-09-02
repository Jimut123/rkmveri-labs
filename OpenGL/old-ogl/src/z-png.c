#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "z-png.h"
#include "debug.h"


void png_read_file(char *filename, struct image_st *img)
{
    FILE *fp = fopen(filename, "rb");

    int width, height;
    png_byte colortype;
    png_byte bitdepth;
    png_byte *pixels;

    png_byte *row;

    png_structp png =
	png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
	abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
	abort();

    if (setjmp(png_jmpbuf(png)))
	abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    colortype = png_get_color_type(png, info);
    bitdepth = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if (bitdepth == 16)
	png_set_strip_16(png);

    if (colortype == PNG_COLOR_TYPE_PALETTE)
	png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (colortype == PNG_COLOR_TYPE_GRAY && bitdepth < 8)
	png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
	png_set_tRNS_to_alpha(png);

    // These colortype don't have an alpha channel then fill it with 0xff.
    if (colortype == PNG_COLOR_TYPE_RGB ||
	colortype == PNG_COLOR_TYPE_GRAY
	|| colortype == PNG_COLOR_TYPE_PALETTE)
	png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (colortype == PNG_COLOR_TYPE_GRAY ||
	colortype == PNG_COLOR_TYPE_GRAY_ALPHA)
	png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    pixels = (png_byte *) malloc(4 * sizeof(png_byte) * height * width);

    int k = 0;

    row = (png_byte *) malloc(png_get_rowbytes(png, info));

    for (int y = 0; y < height; y++) {
	png_read_rows(png, &row, NULL, 1);
	for (int x = 0; x < width; x++) {
	    png_bytep px = &(row[x * 4]);
	    pixels[k++] = px[0];
	    pixels[k++] = px[1];
	    pixels[k++] = px[2];
	    pixels[k++] = px[3];
	}
    }

    free(row);

    img->width = width;
    img->height = height;
    img->colortype = colortype;
    img->bitdepth = bitdepth;
    img->pixels = pixels;

    fclose(fp);
}

void png_free_image(struct image_st *img)
{
    free(img->pixels);
}

void png_write_file(char *filename, struct image_st *img)
{
    int y;

    int width = img->width;
    int height = img->height;
    png_byte *row = NULL;
    png_byte *pixels = img->pixels;

    FILE *fp = fopen(filename, "wb");
    if (!fp)
	abort();

    png_structp png =
	png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
	abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
	abort();

    if (setjmp(png_jmpbuf(png)))
	abort();

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(png,
		 info,
		 width, height,
		 8,
		 PNG_COLOR_TYPE_RGBA,
		 PNG_INTERLACE_NONE,
		 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    //png_set_filler(png, 0, PNG_FILLER_AFTER);

    //png_write_image(png, row_pointers);

    row = (png_byte *) malloc(png_get_rowbytes(png, info));

    int k = 0;

    for (int y = 0; y < height; y++) {
	for (int x = 0; x < width; x++) {
	    png_bytep px = &(row[x * 4]);
	    px[0] = pixels[k++];
	    px[1] = pixels[k++];
	    px[2] = pixels[k++];
	    px[3] = pixels[k++];
	}
	png_write_row(png, row);
    }
    png_write_end(png, NULL);

    free(row);

    fclose(fp);
}

void process_png_file(struct image_st *img)
{
    int height = img->height;
    int width = img->width;

    for (int y = 0; y < height; y++) {
	png_bytep row = &(img->pixels[y * img->width * 4]);
	for (int x = 0; x < width; x++) {
	    png_bytep px = &(row[x * 4]);
	    // Do something awesome for each pixel here...
	    //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
	}
    }
}

/*
int main(int argc, char *argv[]) {
  if(argc != 3) abort();

  read_png_file(argv[1]);
  process_png_file();
  write_png_file(argv[2]);

  return 0;
}
*/
