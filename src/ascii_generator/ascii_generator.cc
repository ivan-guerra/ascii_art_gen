#include "ascii_generator.h"

#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdexcept>
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

AsciiGenerator::ImageType AsciiGenerator::GetImageType(
    const std::string& filename) const {
    static const uint64_t kPngSignature = 0x89504E470D0A1A0A;
    static const uint64_t kJpgSignature = 0xFFD8000000000000;

    /* Read the first 8 bytes of the file. */
    std::ifstream ifs(filename, std::ifstream::binary);
    if (!ifs.is_open()) {
        return ImageType::kUnknown;
    }
    std::vector<char> buffer(8, 0);
    ifs.read(&buffer[0], buffer.size());

    /* Construct an unsigned 64-bit word using the 8 bytes in buffer. */
    uint64_t word = 0;
    for (const char& c : buffer) {
        word = (word << 8) | static_cast<uint8_t>(c);
    }

    /* Check if the word matches a known image file type signature. */
    if (word == kPngSignature) {
        return ImageType::kPng;
    } else if ((word & kJpgSignature) == kJpgSignature) {
        return ImageType::kJpg;
    }
    return ImageType::kUnknown;
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
    switch (GetImageType(filename)) {
        case ImageType::kJpg:
            boost::gil::read_image(filename, image_, boost::gil::jpeg_tag{});
            break;
        case ImageType::kPng:
            boost::gil::read_image(filename, image_, boost::gil::png_tag{});
            break;
        default:
            throw std::invalid_argument(
                "nonexistent file or unsupported format");
    }
}

void AsciiGenerator::Draw(const std::string& outfile) {
    UpdateImage();

    std::ofstream outstream(outfile);
    boost::gil::rgb8_view_t image_view = boost::gil::view(image_);
    for (int j = 0; j < image_view.height(); ++j) {
        boost::gil::rgb8_view_t::x_iterator it_row = image_view.row_begin(j);
        for (int i = 0; i < image_view.width(); ++i) {
            boost::gil::rgb8_pixel_t pixel = it_row[i];
            outstream << GetChar((pixel[0] + pixel[1] + pixel[2]) / 3);
        }
        outstream << std::endl;
    }
}

}  // namespace asciigen
