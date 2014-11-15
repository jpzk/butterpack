#include <fstream>
#include <iostream>
#include <cmath>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

// return the file size
ifstream::pos_type filesize(const char* filename) {
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

// read the data into a buffer
char* read_data(const char* filename) {
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

// encode 
Mat encode(int w, int h, int cells, char *buffer) {
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

// use quorum to guess the value among many
int quorum(int data[], size_t n) {
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

// decoder function 
char* decode(Mat input, int w, int h, int cells) {
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

float test_encoding(const char* filename, int w, int h, int cells) {
    char *input, *reconstructed;
    input = read_data(filename);
    Mat A = encode(w, h, cells, input);
    imwrite("output.jpg", A);

    Mat img = imread("output.jpg");
    reconstructed = decode(img, w, h, cells);

    cout << reconstructed << endl;

    delete[] reconstructed;
    delete[] input;
}

int main() {
    test_encoding("butterpack.cpp", 640, 480, 5);

    return(0);
}
