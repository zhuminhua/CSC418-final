#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  //rgb = rgba;
  //rgb.clear();
  // printf("height %d ", height);
  // printf("width %d ", width);
  // printf("size of RGBA VECTOR %lu", rgba.size());

  // rgb.clear();
  // for (unsigned int i = 0; i < rgba.size(); i++)
  // {
  //   int r = i % 4;
  //   switch(i)
  //   {
  //     case 0:
  //     case 1:
  //     case 2:
  //       rgb.push_back(rgba[i]);
  //       continue;
  //     case 3: 
  //       continue;
  //   }
  // }

  /*for (unsigned int h = 0; h < height; h++) {
    for (unsigned int w = 0; w < width; w++) {
      //int index = rgb.begin() + (h*width+w)*4 + 3;
      //rgb.erase(rgb.begin() + (h*width+w)*4 + 3);
      //index = (h * width + w) * 4;
      int indexBefore = (h * width + w) * 4;
      int indexReduced = (h * width + w) * 3;
      rgb[indexReduced] = rgba[indexBefore];
      rgb[indexReduced + 1] = rgba[indexBefore + 1];
      rgb[indexReduced + 2] = rgba[indexBefore + 2];
    }
  }*/

  /*for (unsigned int h = 0; h < height; h++) {
    for (unsigned int w = 0; w < width; w++) {
      int index = h * width + w;
      rgb[index * 3 + 0] = rgba[index * 4 + 0];
      rgb[index * 3 + 1] = rgba[index * 4 + 1];
      rgb[index * 3 + 2] = rgba[index * 4 + 2];
    }
  }*/

  rgb.clear();

  for (unsigned int i = 0; i < rgba.size(); i++)
  {
    if(i % 4 == 3)
      continue;
    rgb.push_back(rgba[i]);
  }
  //printf("thrid %d", rgb[3]);
  //std::cout << rgb << std::endl;
}