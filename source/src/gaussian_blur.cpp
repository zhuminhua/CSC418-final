#include "gaussian_blur.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm> 

//#define FILTER 18
#define FILTER 3//10

std::vector<int> gaussian_blur(
    const std::string &filename,
    const std::vector<unsigned char> &data,
    const int width,
    const int height,
    const int num_channels)
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    //return false;
    int size = height * width;

    std::string h = std::to_string(height);
    std::string w = std::to_string(width);

    std::ofstream ppmFile;

    // int factor = 1.0 / 18.0;
    // double filter[FILTER][FILTER] =
    // {
    //   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,0, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1, 0, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 1, 0, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 1, 0, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 1, 0, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 1, 0, 
    //   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 1, 
    // };
    // std::vector<int> motion_data;
    // for (unsigned char c: data) {
    //     int i = c;
    //     motion_data.push_back(i);
    // }

    // for (int x = 0; x < height; x++)
    //     for (int y = 0; y < width; y++)
    //     {
    //         int offset = x * 3 * width + y * 3;
    //         double r = 0.0, g = 0.0, b = 0.0;
    //         for (int filterY = 0; filterY < FILTER; filterY++) {
    //             for (int filterX = 0; filterX < FILTER; filterX++)
    //             {
    //                 int imageX = (x - FILTER / 2 + filterX + height) % height;
    //                 // std::cout << imageX << std::endl;
    //                 int imageY = (y - FILTER / 2 + filterY + height) % width;
    //                 int inner_offset = imageX * width * 3 + imageY * 3;
    //                 r += motion_data[inner_offset + 0] * filter[filterY][filterX];
    //                 g += motion_data[inner_offset + 1] * filter[filterY][filterX];
    //                 b += motion_data[inner_offset + 2] * filter[filterY][filterX];
    //             }
    //         }
    //         // std::cout << std::max(int(factor * r), 0) << std::endl;
    //         motion_data[offset + 0] = std::min(std::max(int(factor * r), 0), 255);
    //         motion_data[offset + 1] = std::min(std::max(int(factor * g), 0), 255);
    //         motion_data[offset + 2] = std::min(std::max(int(factor * b), 0), 255);
    //         std::cout << (factor * r) << std::endl;
    //         // std::cout << motion_data[offset + 0] << std::endl;
    //         // std::cout << motion_data[offset + 2] << std::endl;
    //     }


    //guassian blur algorithm 
    //based on http://blog.ivank.net/fastest-gaussian-blur.html

    std::vector<int> motion_data;
    motion_data.reserve(data.size());

    for (auto c: data) {
        motion_data.push_back(int(c));
    }

    double radius = ceil(FILTER * 2.57);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double valueR = 0;
            double valueG = 0;
            double valueB = 0;
            double weight_sum = 0;
            for(int k = i-radius; k < i + radius + 1; k++){
                for(int m = j-radius; m < j + radius + 1; m++){
                    double x = std::min(width - 1, std::max(0, m));
                    double y = std::min(height - 1, std::max(0, k));
                    double distance = (m - j)*(m - j)+(k-i)*(k-i);
                    double weight = exp(-distance/(2.0*FILTER*FILTER))/(M_PI*2*FILTER*FILTER);
                    
                    int index = y*width+x;
                    valueR += data[index *3] * weight;
                    valueG += data[index *3+1] * weight;
                    valueB += data[index *3+2] * weight;

                    weight_sum += weight;
                }
            }
            int index = i*width+j;

            motion_data[index * 3] = (int)(valueR/weight_sum);
            motion_data[index * 3+1] = (int)(valueG/weight_sum);
            motion_data[index * 3+2] = (int)(valueB/weight_sum);
        }
    }

    std::vector<unsigned char> data_new;
    for (int i: motion_data) {
        unsigned char c = i;
        data_new.push_back(c);
    }

    // std::cout << data_new << std::endl;

    ppmFile.open(filename, std::ios::out);
    if (!ppmFile)
    {
        std::cerr << "File open error.";
        return motion_data;
    }

    std::string ppm_data = "";

    if (num_channels == 3)
    {
        ppmFile << "P3 " << w << ' ' << h << ' ' << "255\n";
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int index = i * width + j;
                ppmFile << (int)motion_data[index * 3] << ' ';
                ppmFile << (int)motion_data[index * 3 + 1] << ' ';
                ppmFile << (int)motion_data[index * 3 + 2] << ' ';
            }
            //ppmFile << "\n";
        }
    }
    if (num_channels == 1)
    {
        ppmFile << "P2 " << w << ' ' << h << ' ' << "255\n";
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int index = i * width + j;
                ppmFile << (int)motion_data[index] << ' ';
            }
        }
    }

    ppmFile.close();
    return motion_data;
    ////////////////////////////////////////////////////////////////////////////
}
