#include <stdio.h>
#include "ppm.h"

int main() 
{
  FILE* file = fopen("file.pbm", "wb");

  PPM_WB_IMAGE* image = create_ppm_wb_image(1000, 1000);

  for(int x = 100; x < 400; x++)
    for(int y = 100; y < 400; y++)
      set_wb_image_pixel_color(image, x, y, 1);

  write_wb_image_binary(image, file);

  return 0;
}

