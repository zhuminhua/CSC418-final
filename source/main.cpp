#include "write_ppm.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>
#include "gaussian_blur.h"
#include "ppm.h"
#include "over.h"
#include "rgba_to_rgb.h"
#include "chroma.h"

int main(int argc, char * argv[])
{
  ppm image("../images/cat.ppm");
  image.read("../images/cat.ppm");
  int height = image.height;
  int width = image.width;
  
  int prevW = image.width;
  int prevH = image.height;

  std::vector<unsigned char> data;
  data.reserve(height*width*3);

  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      int index = i * width + j;
      data.push_back(image.r[index]);
      data.push_back(image.g[index]);
      data.push_back(image.b[index]);
    }
  }
  //composing 
  std::vector<unsigned char> next_rgba;
  next_rgba.reserve(width*height*4);
    for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) { 
      int index = i * width + j; 
      next_rgba.push_back(data[index*3]);
      next_rgba.push_back(data[index*3 + 1]);
      next_rgba.push_back(data[index*3 + 2]);
      next_rgba.push_back(255);
    }
  }
  std::vector<unsigned char> chroma_data;
  chroma_data.reserve(height*width*4);
  //chroma(data, chroma_data, width, height, 83,110,50);
  int r = 103;
  int g = 127;
  int b = 37;
  chroma(next_rgba, chroma_data, width , height, r, g, b);
  std::vector<unsigned char> rgb_chroma;
  rgb_chroma.reserve(height*width*4);
  rgba_to_rgb(chroma_data,width,height,rgb_chroma);
  write_ppm("chroma.ppm",rgb_chroma,width, height,3);

  ppm image2("../images/night.ppm");
  image2.read("../images/night.ppm");
  height = image2.height;
  width = image2.width;
  
  data.clear();
  data.reserve(height*width*3);

  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      int index = i * width + j;
      data.push_back(image2.r[index]);
      data.push_back(image2.g[index]);
      data.push_back(image2.b[index]);
    }
  }
  std::vector<int> motion_data;
  motion_data = gaussian_blur("gaussian_blur_night.ppm",data,image2.width,image2.height,3);

  // //composing 
  std::vector<unsigned char> composite_rgba;
  composite_rgba.reserve(height*width*4);
  std::cout<< data.size() << " " << motion_data.size() << std::endl;
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) { 
      int index = i * width + j; 
      composite_rgba.push_back(motion_data[index*3]);
      composite_rgba.push_back(motion_data[index*3 + 1]);
      composite_rgba.push_back(motion_data[index*3 + 2]);
      // composite_rgba.push_back(200);
      composite_rgba.push_back(200);
    }
  }

  // int secW = width;
  // int secH = height;

  // std::vector<unsigned char> before_rgb;
  // rgba_to_rgb(composite_rgba,secW, secH,before_rgb);

  // write_ppm("before.ppm",before_rgb,secW, secH,3);


  width = std::min(prevW, width);
  height = std::min(prevH, height); 
  std::cout<<width<<" "<<height<<std::endl;
  std::cout<<prevW<<" "<<prevH<<std::endl;
  over(chroma_data,composite_rgba,width,height,composite_rgba);

  // //over(composite_rgba,next_rgba,width,height,composite_rgba);
  std::vector<unsigned char> composite_rgb;
  rgba_to_rgb(composite_rgba,image2.width, image2.height,composite_rgb);

  write_ppm("composite_night.ppm",composite_rgb,width, height,3);
}
