#include "ascii_generator.h"

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

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

    boost::gil::rgb8_image_t resized_img(scaled_width, scaled_height);
    boost::gil::resize_view(boost::gil::const_view(image_),
                            boost::gil::view(resized_img),
                            boost::gil::bilinear_sampler{});
    image_ = resized_img;
}

AsciiGenerator::AsciiGenerator(const std::string& filename, float scale_factor,
                               int char_width, int char_height)
    : scale_factor_(scale_factor),
      char_width_(char_width),
      char_height_(char_height) {
    boost::gil::read_image(filename, image_, boost::gil::jpeg_tag{});
}

void AsciiGenerator::Draw() {
    UpdateImage();

    std::ofstream outfile("ascii_art.txt");
    boost::gil::rgb8_view_t image_view = boost::gil::view(image_);
    for (int j = 0; j < image_view.height(); ++j) {
        boost::gil::rgb8_view_t::x_iterator it_row = image_view.row_begin(j);
        for (int i = 0; i < image_view.width(); ++i) {
            boost::gil::rgb8_pixel_t pixel = it_row[i];
            outfile << GetChar((pixel[0] + pixel[1] + pixel[2]) / 3);
        }
        outfile << std::endl;
    }
}

}  // namespace asciigen
