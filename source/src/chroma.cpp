#include "chroma.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

//algorithm based on http://gc-films.com/chromakey.html

double rgb2y (int r, int g, int b) 
{ 
   double y; 
   //y = 0.2126*r/255.0 + 0.7152*g/255.0 + 0.0722*b/255.0; 
   y = 0.2126*r + 0.7152*g + 0.0722*b; 
   return y; 
} 

double rgb2cb (int r, int g, int b) 
{ 
   double cb; 
   //cb = -0.09991*r/255.0 - 0.33609*g/255.0 + 0.436*b/255.0; 
   cb = -0.09991*r - 0.33609*g + 0.436*b; 
   return cb; 
} 

double rgb2cr (int r, int g, int b) 
{ 
   double cr; 
   //cr = 0.615*r/255.0 - 0.55861*g/255.0 - 0.05639*b/255.0; 
   cr = 0.615*r - 0.55861*g - 0.05639*b; 
   return cr; 
} 

void chroma(
    const std::vector<unsigned char> &A,
    std::vector<unsigned char> &B,
    const int &width,
    const int &height,
    const int &rkey,
    const int &gkey,
    const int &bkey)
{
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        double cbKey = rgb2cb(rkey,gkey,bkey);
        double crKey = rgb2cr(rkey,gkey,bkey);
        double ra = 13.5;//13.5;
        double rb = 18.0;//16.0;

        int index = i * width + j;
        int r = A[index*4];
        int g = A[index*4 + 1];
        int b = A[index*4 + 2];

        double cb = rgb2cb(r,g,b);
        double cr = rgb2cr(r,g,b);

        double mask;
        double temp = sqrt((cbKey-cb)*(cbKey-cb)+(crKey - cr)*(crKey - cr));
        int outA;
        
        //std::cout<<temp<<std::endl;
        if (temp < ra) {
            mask = 1.0;
            outA = 0;
        }   
        else if (temp < rb) {
            mask = 1.0 - ((temp-ra)/(rb-ra));
            outA = ((temp-ra)/(rb-ra)) * A[index*3 + 3];

        }
        else {
            mask = 0.0;
            outA = A[index*4 + 3];
        }
        B.push_back(std::max(int(r - mask*rkey), 0));
        B.push_back(std::max(int(g - mask*gkey), 0));
        B.push_back(std::max(int(b - mask*bkey), 0));
        B.push_back(outA);
      
      }
    }
}


