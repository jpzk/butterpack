#include "include/butterpack_codec.hpp"
#include "include/butterpack.hpp"

int main(int argc, char **argv) {
    Butterpack *butterpack;
    butterpack = new Butterpack();
    butterpack->encode(640, 480, 5, "src/butterpack.cpp","out.jpg");
    delete butterpack;
    return(0);
};
