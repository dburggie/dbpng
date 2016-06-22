
#include <xspng.h>
#include <private_xspng.h>

#include <stdio.h>  //fwrite, FILE*
#include <stdint.h> //uint8_t, uint32_t
#include <stdlib.h> //malloc, free
#include <string.h> //memset
#include <assert.h> //assert



//allocate a new imagep object and allocate it's buffer
xspng_imagep xspng_image_new(xspng_int width, xspng_int height) {

	assert(0 < width);
	assert(0 < height);

	xspng_imagep imgp = (xspng_imagep) malloc(sizeof (xspng_image));
	if (!imgp) return NULL;

	img->buffer = NULL;
	img->width = width;
	img->height = height;

	xspng_image_init(img);

	return img;
}



//free an imagep object (and it's buffer) you're done with
void xspng_image_free(xspng_imagep imgp) {
	if (img) {
		if (img->buffer) {
			free(img->buffer);
			img->width = 0;
			img->height = 0;
			img->buffer = NULL;
		}
		free(img);
	}
}



//allocate new buffer for an existing image struct
void xspng_image_init(xspng_image *img) {
	assert(NULL != img);
	assert(0 < img->width);
	assert(0 < img->height);

	if (img->buffer) free(img->buffer);

	size_t footprint = img->width * img->height * 4 * sizeof(xspng_byte);
	size_t stride = img->width * 4;

	img->buffer = (xspng_byte*) malloc(footprint);
	
	if (!img->buffer) {
		img->width = 0;
		img->height = 0;
	}
	
	else {
		xspng_int x, y;
		for (y = 0; y < img->height; y++) {
			for (x = 0; x < img->width; x++) {
				img->buffer[y*stride + x*4 + 0] = 0x00;
				img->buffer[y*stride + x*4 + 1] = 0x00;
				img->buffer[y*stride + x*4 + 2] = 0x00;
				img->buffer[y*stride + x*4 + 3] = 0xff;
			}
		}
	}
}



//set rgb values of a given (x,y) coordinate, leave alpha alone
void xspng_image_set_rgb(
		xspng_imagep img,
		xspng_int x, xspng_int y,
		xspng_byte r, xspng_byte g, xspng_byte b
) {
	assert(NULL != img);
	assert(NULL != img->buffer);
	assert(0 <= x);
	assert(0 <= y);
	assert(x < img->width);
	assert(y < img->height);

	xspng_int stride = 4 * img->width;
	img->buffer[y * stride + x * 4    ] = r;
	img->buffer[y * stride + x * 4 + 1] = g;
	img->buffer[y * stride + x * 4 + 2] = b;
}



//set a pixel to the given red-green-blue-alpha samples
void xspng_image_set_rgba(
		xspng_imagep img,
		xspng_int x, xspng_int y,
		xspng_byte r, xspng_byte g, xspng_byte b, xspng_byte a
) {
	assert(NULL != img);
	assert(NULL != img->buffer);
	assert(0 <= x);
	assert(0 <= y);
	assert(x < img->width);
	assert(y < img->height);

	xspng_int stride = 4 * img->width;
	img->buffer[y * stride + x * 4    ] = r;
	img->buffer[y * stride + x * 4 + 1] = g;
	img->buffer[y * stride + x * 4 + 2] = b;
	img->buffer[y * stride + x * 4 + 3] = a;
}



void xspng_image_write(xspng_imagep img, const char * filename) { }

