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

using namespace std;
using namespace cv;

/**
 * Returns the file size of a file
 *
 * @param filename char* pointer to filename
 */
ifstream::pos_type ButterpackCodec::filesize(const char* filename) {
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

/**
 * Read data from filename
 *
 * @param filename char* pointer to filename
 */
char* ButterpackCodec::read_data(const char* filename) {
    char *buffer;

    ifstream file;
    file.open(filename, ios::in | ios::binary);
    if(file.is_open()) {
        buffer = new char[filesize(filename)];
        file.seekg(0, ios::beg);
        file.read(buffer, filesize(filename));
        file.close();
        return(buffer); 
    } else {
        return(NULL);
    }
}

/** 
 * Encodes buffer into a vector of opencv images
 * 
 * @param w int width of the image
 * @param h int height of the image
 * @param cells int cell size, width and height
 * @param buffer char* pointer to the input buffer
 */
vector<Mat> ButterpackCodec::encode(int w, int h, int cells, char *buffer) {
    
    vector<Mat> output;
    
    float space = ((float) w / (float) cells) * ((float) h / (float) cells);
    float bytes = (float) sizeof(buffer) / (float) sizeof(char);

    int images = ceil(bytes / space);
    cout << images << endl;

    return output;
}

/**
 * Decodes a vector of Mat images into a buffer 
 *
 * @param inputs vector<Mat> vector of input images
 * @param w int width of the input images
 * @param h int height of the input images
 * @param cells int cell size of the input images
 */
char* ButterpackCodec::decode(vector<Mat> inputs, int w, int h, int cells) {

    char *buffer;
    return buffer;
} 

/**
 * Encodes buffer into a single opencv image
 * 
 * @param w int width of the image
 * @param h int height of the image
 * @param cells int cell size, width and height
 * @param buffer char* pointer to the input buffer
 */
 Mat ButterpackCodec::encode_single(int w, int h, int cells, char *buffer) {
    Mat A( h, w, CV_8UC3, Scalar(0,0,0));

    int bytes = (w / cells) * (h / cells);
    char bits[bytes * 8];
    
    // get the bits
    int bit_index = 0;
    for(int i = 0; i < bytes; i++) {
        for(int b = 0; b < 8; b++) {
            bits[bit_index] = ((buffer[i] >> b) & 1);
            bit_index++;
        } 
    } 

    int bits_offset = 0;
    for(int i = 0; i < (h / cells); i++) {
        for(int j = 0; j < (w / cells); j++) {
            for(int ci = 0; ci < cells; ci++) {
                for(int cj = 0; cj < cells; cj++) {
                    int x = i * cells + ci;
                    int y = j * cells + cj;
                    int color = bits[bits_offset] * 255;
                    A.at<Vec3b>(x,y) = Vec3b(color,color,color);
                }
            }
            // next data point
            bits_offset++;
        };
    };
    return(A); 
}

/**
 * Returns the int value of the most common value
 * in the data array
 *
 * @data int array with values
 * @n size_t of the array
 */
int ButterpackCodec::quorum(int data[], size_t n) {
    int diversity = 1;
    int old = data[0];
    int *unique = new int[n];
    unique[0] = data[0];

    for(int i = 1; i < n; i++) {
        if(old != data[i]) {
            unique[diversity] = data[i];
            diversity++;
            old = data[i];
        };
    };

    int *frequencies = new int[diversity];
    for(int i = 0; i < diversity; i++) {
        frequencies[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < diversity; k++) {
            if(unique[k] == data[i]) {
                frequencies[k]++;
            }
        } 
    }

    int most_unique_index = 0;
    int most_unique = frequencies[0];
    for(int i = 1; i < diversity; i++) {
        if(frequencies[i] > most_unique) {
            most_unique_index = i;
            most_unique = frequencies[0];
        } 
    }
   
    int result = unique[most_unique_index];
    delete[] unique;
    delete[] frequencies;

    return(result);
}

/**
 * Decode a single openCV image to buffer
 *
 * @param input Mat image 
 * @param w int width of the image
 * @param h int height of the image
 * @param cells int cell size, width and height
 */
char* ButterpackCodec::decode_single(Mat input, int w, int h, int cells) {
    int bits_offset = 0;
    int bits = (w / cells) * (h / cells);
    int *buffer = new int[bits];
   
    for(int i = 0; i < (h / cells); i++) {
        for(int j = 0; j < (w / cells); j++) {

            int redundant_data[cells * cells];
            int rd_index = 0;

            for(int ci = 0; ci < cells; ci++) {
                for(int cj = 0; cj < cells; cj++) {
                    int x = i * cells + ci;
                    int y = j * cells + cj;
                    Vec3b point = input.at<Vec3b>(x,y);
                    int color = point.val[0];
                    redundant_data[rd_index] = color;
                    rd_index++;
                }
            }
            buffer[bits_offset] = quorum(redundant_data, cells*cells);
            // next data point
            bits_offset++;
        };
    };

    // decode into bytes
    int byte_counter = 0;
    char *output = new char[bits / 8];
    for(int i = 0; i < bits; i += 8) {
        char result = (char) 0;

        for(int b = 0; b < 8; b++) {
            if(buffer[i + b] > 100) {
                result += pow(2, b);
            }
        }
        output[byte_counter] = result;
        byte_counter++;
    }

    return(output);
}


