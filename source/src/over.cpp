#include "over.h"

void over(
    const std::vector<unsigned char> &A,
    const std::vector<unsigned char> &B,
    const int &width,
    const int &height,
    std::vector<unsigned char> &C)
{
  //C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  //C.resize(A.size());
  
  for (unsigned int h = 0; h < height; h++){
    for (unsigned int j = 0; j < width; j++)
  {
    int i = (h * width + j) * 4;
    double alphaA = A[i + 3] / 255.0;
    double alphaB = B[i + 3] / 255.0;
    double outA = 1 - (1-alphaA)*(1-alphaB);

    C[i] = ((alphaA / outA) * A[i] + (1 - alphaA / outA) * B[i]);
    C[i + 1] = ((alphaA / outA) * A[i+1] + (1 - alphaA / outA) * B[i+1]);
    C[i + 2] = ((alphaA / outA) * A[i+2] + (1 - alphaA / outA) * B[i+2]);
    C[i + 3] = outA*255.0;

  }
  }

}
