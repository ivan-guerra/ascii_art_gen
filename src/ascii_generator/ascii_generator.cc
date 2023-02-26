#include "ascii_generator.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "CImg.h"

namespace asciigen {

char AsciiGenerator::GetChar(int value) {
    static const std::string kAsciiChars =
        " .'`^\",:;Il!i><~+_-?][}{1)(|\\/"
        "tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    static const float kInterval = kAsciiChars.size() / 256.f;

    return kAsciiChars[std::floor(value * kInterval)];
}

void AsciiGenerator::UpdateImage() {
    float char_scaling = char_width_ / static_cast<float>(char_height_);
    int scaled_width = image_.width() * scale_factor_;
    int scaled_height = image_.height() * scale_factor_ * char_scaling;

    image_.resize(scaled_width, scaled_height);
}

AsciiGenerator::AsciiGenerator(const std::string& filename, float scale_factor,
                               int char_width, int char_height)
    : scale_factor_(scale_factor),
      char_width_(char_width),
      char_height_(char_height),
      image_(filename.c_str()) {}

void AsciiGenerator::Draw() {
    UpdateImage();

    std::ofstream outfile("ascii_art.txt");
    std::vector<unsigned int> rgb(3, 0);
    for (int i = 0; i < image_.height(); ++i) {
        for (int j = 0; j < image_.width(); ++j) {
            rgb[0] = image_(j, i, 0);
            rgb[1] = image_(j, i, 1);
            rgb[2] = image_(j, i, 2);
            int average = std::accumulate(rgb.begin(), rgb.end(), 0) / 3;
            outfile << GetChar(average);
        }
        outfile << std::endl;
    }
}

}  // namespace asciigen
