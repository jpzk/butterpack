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

#include <iostream>

#include "include/butterpack_codec.hpp"
#include "include/butterpack.hpp"

int main(int argc, char **argv) {

    if(argc < 4 && argv[1] != "-d" && argv[1] != "-e") {
        cout << "butterpack -d/-e input output" << endl;
        return(-1);
    }

    Butterpack *butterpack = new Butterpack();
 
    if(strcmp(argv[1],"-e") == 0) {
        cout << "encode" << endl;
        butterpack->encode(640, 480, 5, argv[2], argv[3]);
    } else {
        butterpack->decode(640, 480, 5, argv[2], argv[3]);
    }

    delete butterpack;
    return(0);
};
