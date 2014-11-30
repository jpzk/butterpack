/*

This file is part of butterpack.

butterpack is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

butterpack is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with butterpack.  If not, see <http://www.gnu.org/licenses/>.
*/

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
        int images(int w, int h, int cells, int bytes);
        int bytes(int w, int h, int cells);
        vector<Mat> encode(int w, int h, int cells, char *buffer);
        char* decode(vector<Mat> input, int w, int h, int cells);
        Mat encode_single(int w, int h, int cells, char *buffer);
        char* decode_single(Mat input, int w, int h, int cells);
        char *read_data(const char *filename);
        int quorum(int data[], size_t n);
        ifstream::pos_type filesize(const char *filename);
};
