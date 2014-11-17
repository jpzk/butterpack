#ifndef __BUTTERPACK_CODEC_HPP
#define __BUTTERPACK_CODEC_HPP
#endif

#include <fstream>
#include <iostream>
#include <cmath>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class ButterpackCodec {
    public:
        Mat encode(int w, int h, int cells, char *buffer);
        char* decode(Mat input, int w, int h, int cells);
        char *read_data(const char *filename);
        int quorum(int data[], size_t n);
        ifstream::pos_type filesize(const char *filename);
};
