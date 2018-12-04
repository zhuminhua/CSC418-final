#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images or email
  // jacobson@cs.toronto.edu for correct code.
  //return false;
  int size = height * width;

  std::string h = std::to_string(height);
  std::string w = std::to_string(width);

  std::ofstream ppmFile;

  ppmFile.open(filename, std::ios::out);
  if (!ppmFile)
  {
    std::cerr << "File open error.";
    return false;
  }

  std::string ppm_data = "";

   if (num_channels == 3) { 
    ppmFile << "P3 " << w << ' ' << h << ' '<< "255\n";
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        int index = i * width + j;
        ppmFile << (int)data[index * 3] << ' ';
        ppmFile << (int)data[index * 3 + 1] << ' '; 
        ppmFile << (int)data[index * 3 + 2] << ' '; 
      }
      //ppmFile << "\n";
    }
  }
  if (num_channels == 1)
  {
    ppmFile << "P2 " << w << ' ' << h << ' '<< "255\n";
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        int index = i * width + j;
        ppmFile << (int)data[index] << ' ';
      }
    }
  }
  
  ppmFile.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
