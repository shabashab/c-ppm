#ifndef PPM_H
#define PPM_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

bool get_wb_image_pixel(PPM_WB_IMAGE* image, size_t x, size_t y);
uint8_t get_graymap_image_pixel(PPM_GRAYMAP_IMAGE* image, size_t x, size_t y);
RGB_PIXEL get_pixmap_image_pixel(PPM_PIXMAP_IMAGE* image, size_t x, size_t y);

void set_wb_image_pixel_color(PPM_WB_IMAGE* image, size_t x, size_t y, bool color);
void set_graymap_image_pixel_color(PPM_GRAYMAP_IMAGE* image, size_t x, size_t y, uint8_t color);
void set_pixmap_image_pixel_color(PPM_PIXMAP_IMAGE* image, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);

void free_wb_image(PPM_WB_IMAGE* image);
void free_graymap_image(PPM_GRAYMAP_IMAGE* image);
void free_pixmap_image(PPM_PIXMAP_IMAGE* image);

#ifndef PPM_IMPL
#define PPM_IMPL

void throw_fatal(const char* text, int status) 
{
  printf("FATAL: %s", text);
  exit(status);
}

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
void check_pixel_position(size_t x, size_t y, PPM_IMAGE_META *meta)
{
  if(x > (meta->width - 1))
    throw_fatal("Can't get a pixel that is outside image", 1);
    
  if(y > (meta->height - 1))
    throw_fatal("Can't get a pixel that is outside image", 1);
}

uint8_t* get_pixel_by_pos(uint8_t *pixels, PPM_IMAGE_META *meta, size_t pixel_size, size_t x, size_t y)
{ 
  return pixels + (pixel_size + ((meta->width) * y) + x);
}

bool get_wb_image_pixel(PPM_WB_IMAGE* image, size_t x, size_t y)
{
  check_pixel_position(x, y, &(image->meta));
  return *(bool*)get_pixel_by_pos((uint8_t*)image->pixels, &(image->meta), sizeof(bool), x, y);
}

uint8_t get_graymap_image_pixel(PPM_GRAYMAP_IMAGE* image, size_t x, size_t y)
{
  check_pixel_position(x, y, &(image->meta));
  return *(uint8_t*)get_pixel_by_pos((uint8_t*)image->pixels, &(image->meta), sizeof(uint8_t), x, y);
}

RGB_PIXEL get_pixmap_image_pixel(PPM_PIXMAP_IMAGE* image, size_t x, size_t y)
{
  check_pixel_position(x, y, &(image->meta));
  return image->pixels[(image->meta.width * y) + x];
;
}

void set_wb_image_pixel_color(PPM_WB_IMAGE* image, size_t x, size_t y, bool color)
{
  check_pixel_position(x, y, &(image->meta));
  (*(bool*)get_pixel_by_pos((uint8_t*)image->pixels, &(image->meta), sizeof(bool), x, y)) = color;
}

void set_graymap_image_pixel_color(PPM_GRAYMAP_IMAGE* image, size_t x, size_t y, uint8_t color)
{
  check_pixel_position(x, y, &(image->meta));
  (*(uint8_t*)get_pixel_by_pos((uint8_t*)image->pixels, &(image->meta), sizeof(uint8_t), x, y)) = color;
}

void set_pixmap_image_pixel_color(PPM_PIXMAP_IMAGE* image, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b)
{
  check_pixel_position(x, y, &(image->meta));
  RGB_PIXEL* pixel = &(image->pixels[(image->meta.width * y) + x]);

  pixel->r = r;
  pixel->g = g;
  pixel->b = b;
}


void write_wb_image_plain(PPM_WB_IMAGE* image, FILE* file)
{
  if(!file)
    throw_fatal("File is null", 2);

  fprintf(file, "P1\n%lu %lu\n", image->meta.width, image->meta.height);

  for(size_t i = 0; i < image->pixels_count; i++)
    fprintf(file, "%d\n", image->pixels[i] % 2);
}

void write_graymap_image_plain(PPM_GRAYMAP_IMAGE* image, FILE* file)
{
  if(!file)
    throw_fatal("File is null", 2);

  fprintf(file, "P2 %lu %lu %d\n", image->meta.width, image->meta.height, 255);

  for(size_t i = 0; i < image->pixels_count; i++)
    fprintf(file, "%d\n", image->pixels[i] % 255);
}

void write_pixmap_image_plain(PPM_PIXMAP_IMAGE* image, FILE* file)
{
  if(!file)
    throw_fatal("File is null", 2);

  fprintf(file, "P3 %lu %lu %d\n", image->meta.width, image->meta.height, 255);

  for(size_t i = 0; i < image->pixels_count; i++)
  {
    fprintf(file, "%d %d %d\n", image->pixels[i].r, image->pixels[i].g, image->pixels[i].b);
  }
}


void write_wb_image_binary(PPM_WB_IMAGE* image, FILE* file)
{
  if(!file)
    throw_fatal("File is null", 2);

  fprintf(file, "P4\n%lu %lu\n", image->meta.width, image->meta.height);

  size_t buffer_len = ((image->meta.width / 8)) + (image->meta.width % 8 != 0);

  for(size_t y = 0; y < image->meta.height; y++)
  {
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * buffer_len);
    for(size_t x = 0; x < image->meta.width; x++) 
    {
      buffer[x / 8] |= image->pixels[(y * image->meta.width) + x] << (8 - (x % 8) - 1);
    }
    fwrite(buffer, sizeof(uint8_t), buffer_len, file);
  }
}

void write_graymap_image_binary(PPM_GRAYMAP_IMAGE* image, FILE* file)
{
  if(!file)
    throw_fatal("File is null", 2);
  

  fprintf(file, "P5 %lu %lu %d\n", image->meta.width, image->meta.height, 255);

  uint8_t buffer[1];

  for(size_t i = 0; i < image->pixels_count; i++)
  {
    buffer[0] = image->pixels[i];
    fwrite(buffer, sizeof(uint8_t), 1, file);
  }
}

void write_pixmap_image_binary(PPM_PIXMAP_IMAGE* image, FILE* file)
{
  if(!file)
    throw_fatal("File is null", 2);
  

  fprintf(file, "P6 %lu %lu %d\n", image->meta.width, image->meta.height, 255);

  uint8_t buffer[3];

  for(size_t i = 0; i < image->pixels_count; i++)
  {
    buffer[0] = image->pixels[i].r;
    buffer[1] = image->pixels[i].g;
    buffer[2] = image->pixels[i].b;

    fwrite(buffer, sizeof(uint8_t), 3, file);
  }
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
