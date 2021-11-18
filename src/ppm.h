#include <stdint.h>
#include <stdlib.h>

enum PPM_IMAGE_TYPE {
  WB = 0,
  GRAYMAP = 1,
  PIXMAP = 2
};

typedef struct {
  bool value;
} WB_PIXEL;

typedef struct {
  uint8_t value;
} GRAYMAP_PIXEL;

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} PIXMAP_PIXEL;

typedef struct {
  size_t width;
  size_t height;
  PPM_IMAGE_TYPE type;
} PPM_IMAGE_META;

typedef struct {
  PPM_IMAGE_META meta;

  WB_PIXEL* pixels;
  size_t pixels_count;
} PPM_WB_IMAGE;

typedef struct {
  PPM_IMAGE_META meta;

  GRAYMAP_PIXEL* pixels;
  size_t pixels_count;
} PPM_GRAYMAP_IMAGE;

typedef struct {
  PPM_IMAGE_META meta;

  GRAYMAP_PIXEL* pixels;
  size_t pixels_count;
} PPM_PIXMAP_IMAGE;

PPM_WB_IMAGE* create_ppm_wb_image(size_t width, size_t height);
PPM_GRAYMAP_IMAGE* create_ppm_graymap_image(size_t width, size_t height);
PPM_PIXMAP_IMAGE* create_ppm_pixmap_image(size_t width, size_t height);

PPM_GRAYMAP_IMAGE* ppm_wb_to_graymap(PPM_WB_IMAGE* image);
PPM_PIXMAP_IMAGE* ppm_wb_to_pixmap(PPM_WB_IMAGE* image);
PPM_PIXMAP_IMAGE* ppm_graymap_to_pixmap(PPM_GRAYMAP_IMAGE* image);

void save_wb_image_plain(PPM_WB_IMAGE* image, const char* filename);
void save_graymap_image_plain(PPM_GRAYMAP_IMAGE* image, const char* filename);
void save_pixmap_image_plain(PPM_PIXMAP_IMAGE* image, const char* filename);

void save_wb_image_binary(PPM_WB_IMAGE* image, const char* filename);
void save_graymap_image_binary(PPM_GRAYMAP_IMAGE* image, const char* filename);
void save_pixmap_image_binary(PPM_PIXMAP_IMAGE* image, const char* filename);

WB_PIXEL* get_wb_image_pixel();
GRAYMAP_PIXEL* get_graymap_image_pixel();
PIXMAP_PIXEL* get_pixmap_image_pixel();

void set_wb_image_pixel_color(PPM_WB_IMAGE* image, size_t x, size_t y, bool color);
void set_graymap_image_pixel_color(PPM_GRAYMAP_IMAGE* image, size_t x, size_t y, uint8_t color);
void set_pixmap_image_pixel_color(PPM_PIXMAP_IMAGE* image, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);

void free_wb_image(PPM_WB_IMAGE* image);
void free_graymap_image(PPM_GRAYMAP_IMAGE* image);
void free_pixmap_image(PPM_PIXMAP_IMAGE* image);

#ifndef PPM_IMPL
#define PPM_IMPL

//Implementation goes here

#endif
