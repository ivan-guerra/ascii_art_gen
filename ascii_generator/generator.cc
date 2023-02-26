#include <cstdlib>
#include <fstream>
#include <iostream>

#include "ascii_generator.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "error: missing input image file path" << std::endl;
        std::cerr << "usage: asciigen IMAGE" << std::endl;
        exit(EXIT_FAILURE);
    }

    float scale_factor = 0.8;
    int char_width = 10;
    int char_height = 18;

    try {
        asciigen::AsciiGenerator img_generator(argv[1], scale_factor,
                                               char_width, char_height);
        img_generator.Draw();
    } catch (const std::ifstream::failure& e) {
        std::cerr << "error: could not open file '" << argv[1] << "'"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
