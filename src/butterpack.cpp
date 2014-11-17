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

