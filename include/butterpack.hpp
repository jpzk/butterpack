#ifndef __BUTTERPACK_HPP
#define __BUTTERPACK_HPP
#endif

class Butterpack {
    public:
        void encode(int w, int h, int cells, char *in, char *out);
        void decode(int w, int h, int cells, char *in, char *out);
};
