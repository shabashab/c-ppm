#include <stdio.h>
#include "ppm.h"

int main() 
{
  FILE* file = fopen("file.pbm", "wb");

  PPM_PIXMAP_IMAGE* image = create_ppm_pixmap_image(100, 100);

  for(int x = 20; x <= 80; x++)
    for(int y = 20; y <= 80; y++)
      set_pixmap_image_pixel_color(image, x, y, 0, 255, 255);

  write_pixmap_image_binary(image, file);

  return 0;
}

