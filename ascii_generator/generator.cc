#include <cstdlib>
#include <iostream>

#include "CImg.h"
#include "ascii_generator.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "error: missing input image file path" << std::endl;
        std::cerr << "usage: asciigen IMAGE" << std::endl;
        exit(EXIT_FAILURE);
    }

    float scale_factor = 0.5;
    int char_width = 10;
    int char_height = 18;

    try {
        asciigen::AsciiGenerator img_generator(argv[1], scale_factor,
                                               char_width, char_height);
        img_generator.Draw();
    } catch (const cimg_library::CImgIOException& e) {
        std::cerr << "error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
