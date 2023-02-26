#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "ascii_generator.h"

void PrintUsage() {
    std::cout << "usage: asciigen [OPTIONS]... IMAGE" << std::endl;
    std::cout << "generate an ASCII art text file from an JPG or PNG image"
              << std::endl;
    std::cout << "\t-s\timage scaling factor in the range [0,1]" << std::endl;
    std::cout << "\t-x\tcharacter height" << std::endl;
    std::cout << "\t-y\tcharacter width" << std::endl;
    std::cout << "\t-h\tprint this help page" << std::endl;
}

int main(int argc, char** argv) {
    float scale_factor = asciigen::AsciiGenerator::kDefaultScaleFactor;
    int char_width = asciigen::AsciiGenerator::kDefaultCharWidth;
    int char_height = asciigen::AsciiGenerator::kDefaultCharHeight;

    char c = '\0';
    opterr = 0;
    while (-1 != (c = getopt(argc, argv, "hs:x:y:"))) {
        switch (c) {
            case 'h':
                PrintUsage();
                exit(EXIT_SUCCESS);
                break;
            case 's':
                scale_factor = std::stof(optarg);
                break;
            case 'x':
                char_height = std::stoi(optarg);
                break;
            case 'y':
                char_width = std::stoi(optarg);
                break;
            case '?':
                if (('s' == optopt) || ('x' == optopt) || ('y' == optopt)) {
                    std::cerr << "error: option -" << static_cast<char>(optopt)
                              << " requires an argument" << std::endl;
                } else if (isprint(optopt)) {
                    std::cerr << "error: unknown option '-"
                              << static_cast<char>(optopt) << "'" << std::endl;
                } else {
                    std::cerr << "error: unknown option character '0x"
                              << std::setfill('0') << std::setw(2) << std::hex
                              << optopt << "'" << std::endl;
                }
                exit(EXIT_FAILURE);
            default:
                exit(EXIT_FAILURE);
        }
    }

    if (!argv[optind]) {
        std::cerr << "error: missing image file path" << std::endl;
        std::cerr << "run 'asciigen -h' for help" << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
        asciigen::AsciiGenerator img_generator(argv[optind], scale_factor,
                                               char_width, char_height);
        img_generator.Draw();
    } catch (const std::ifstream::failure& e) {
        std::cerr << "error: could not open file '" << argv[optind] << "'"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
