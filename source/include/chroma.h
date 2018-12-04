#ifndef CHROMA_H
#define CHROMA_H

#include <vector>
#include <string>

void chroma(
    const std::vector<unsigned char> &A,
    std::vector<unsigned char> &B,
    const int &width,
    const int &height,
    const int &rkey,
    const int &gkey,
    const int &bkey);

#endif