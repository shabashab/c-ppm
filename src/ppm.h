#ifndef PPM_H
#define PPM_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB_PIXEL;

typedef struct {
  size_t width;
  size_t height;
} PPM_IMAGE_META;

typedef struct {
  PPM_IMAGE_META meta;

  bool* pixels;
  size_t pixels_count;
} PPM_WB_IMAGE;

typedef struct {
  PPM_IMAGE_META meta;

  uint8_t* pixels;
  size_t pixels_count;
} PPM_GRAYMAP_IMAGE;

typedef struct {
  PPM_IMAGE_META meta;

  RGB_PIXEL* pixels;
  size_t pixels_count;
} PPM_PIXMAP_IMAGE;

PPM_WB_IMAGE* create_ppm_wb_image(size_t width, size_t height);
PPM_GRAYMAP_IMAGE* create_ppm_graymap_image(size_t width, size_t height);
PPM_PIXMAP_IMAGE* create_ppm_pixmap_image(size_t width, size_t height);

PPM_GRAYMAP_IMAGE* ppm_wb_to_graymap(PPM_WB_IMAGE* image);
PPM_PIXMAP_IMAGE* ppm_wb_to_pixmap(PPM_WB_IMAGE* image);
PPM_PIXMAP_IMAGE* ppm_graymap_to_pixmap(PPM_GRAYMAP_IMAGE* image);

void write_wb_image_plain(PPM_WB_IMAGE* image, FILE* file);
void write_graymap_image_plain(PPM_GRAYMAP_IMAGE* image, FILE* file);
void write_pixmap_image_plain(PPM_PIXMAP_IMAGE* image, FILE* file);

void write_wb_image_binary(PPM_WB_IMAGE* image, FILE* file);
void write_graymap_image_binary(PPM_GRAYMAP_IMAGE* image, FILE* file);
void write_pixmap_image_binary(PPM_PIXMAP_IMAGE* image, FILE* file);

bool get_wb_image_pixel(size_t x, size_t y);
uint8_t get_graymap_image_pixel(size_t x, size_t y);
RGB_PIXEL get_pixmap_image_pixel(size_t x, size_t y);

void set_wb_image_pixel_color(PPM_WB_IMAGE* image, size_t x, size_t y, bool color);
void set_graymap_image_pixel_color(PPM_GRAYMAP_IMAGE* image, size_t x, size_t y, uint8_t color);
void set_pixmap_image_pixel_color(PPM_PIXMAP_IMAGE* image, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);

void free_wb_image(PPM_WB_IMAGE* image);
void free_graymap_image(PPM_GRAYMAP_IMAGE* image);
void free_pixmap_image(PPM_PIXMAP_IMAGE* image);

#ifndef PPM_IMPL
#define PPM_IMPL

PPM_WB_IMAGE* create_ppm_wb_image(size_t width, size_t height)
{
  PPM_WB_IMAGE* image = (PPM_WB_IMAGE*)malloc(sizeof(PPM_WB_IMAGE));

  image->meta.width = width;
  image->meta.height = height;

  image->pixels_count = width * height;
  image->pixels = (bool*)malloc(sizeof(bool) * image->pixels_count);

  return image;
}

PPM_GRAYMAP_IMAGE* create_ppm_graymap_image(size_t width, size_t height)
{
  PPM_GRAYMAP_IMAGE* image = (PPM_GRAYMAP_IMAGE*)malloc(sizeof(PPM_GRAYMAP_IMAGE));
  
  image->meta.width = width;
  image->meta.height = height;

  image->pixels_count = width * height;
  image->pixels = (uint8_t*)malloc(sizeof(uint8_t) * image->pixels_count);

  return image;
}

PPM_PIXMAP_IMAGE* create_ppm_pixmap_image(size_t width, size_t height)
{
  PPM_PIXMAP_IMAGE* image = (PPM_PIXMAP_IMAGE*)malloc(sizeof(PPM_PIXMAP_IMAGE));
  
  image->meta.width = width;
  image->meta.height = height;

  image->pixels_count = width * height;
  image->pixels = (RGB_PIXEL*)malloc(sizeof(RGB_PIXEL) * image->pixels_count);

  return image;
}



void free_wb_image(PPM_WB_IMAGE* image)
{
  free(image->pixels);
  free(image);
}

void free_graymap_image(PPM_GRAYMAP_IMAGE* image)
{
  free(image->pixels);
  free(image);
}

void free_pixmap_image(PPM_PIXMAP_IMAGE* image)
{
  free(image->pixels);
  free(image);
}

#endif

#endif
