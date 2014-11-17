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

#include <fstream>
#include <iostream>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "include/butterpack_codec.hpp"
#include "include/butterpack.hpp"

using namespace std;
using namespace cv;

void Butterpack::encode(int w, int h, int cells, char *in, char *out) {
    ButterpackCodec *codec;
    char *input_data;

    codec = new ButterpackCodec();
    input_data = codec->read_data(in);

    Mat image = codec->encode(w, h, cells, input_data);
    imwrite(out, image);

    delete[] input_data;
    delete codec;
};

void Butterpack::decode(int w, int h, int cells, char *in, char *out) {
    ButterpackCodec *codec;
    codec = new ButterpackCodec();

    char *data;    
    Mat image = imread(in);
    data = codec->decode(image, w, h, cells);
    cout << data << endl;

    delete[] data;
    delete codec;
};

