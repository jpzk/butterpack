# butterpack

butterpack is a C++ revamp of [Butterpack_File-2-Video](https://github.com/BackendButters/Butterpack_File-2-Video) based on [OpenCV 2.0](https://github.com/Itseez/opencv). It is a **proof of concept**. butterpack is an encoder and decoder, which allow you to store any file in an image and read the file from the image.The simple bit encoding is bold, but easy to understand and robust.

<pre>
$ cmake .
$ make
$ ./butterpack -e src/butterpack.cpp encoded.jpg
$ ./butterpack -d encoded.jpg butterpack_decoded.cpp
</pre>


# Example 

Here is an example of how the output might look like. In this image the **butterencode.cpp** source code is embedded into the image.The image width is 640, height is 480 and cell size is 5.

![butterpack.cpp](http://i.imgur.com/Ui5xYnB.jpg)

# One Channel Encoding 

For now, butterpack stores the file as binary digits in the image. The parameters are image width, height and cell size. The latter specificies how big the cells for representative bits are. In the current state of the project, all RGB channels are used to store the same bit. Multi channel encoding is tested soon. :)

