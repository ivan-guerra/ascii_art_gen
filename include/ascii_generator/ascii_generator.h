#ifndef ASCII_GENERATOR_H_
#define ASCII_GENERATOR_H_

#include <string>

#include "CImg.h"

namespace asciigen {

class AsciiGenerator {
   public:
    AsciiGenerator() = delete;
    AsciiGenerator(const std::string& filename, float scale_factor = 1.f,
                   int char_width = 10, int char_height = 18);
    ~AsciiGenerator() = default;
    AsciiGenerator(const AsciiGenerator&) = default;
    AsciiGenerator& operator=(const AsciiGenerator&) = default;
    AsciiGenerator(AsciiGenerator&&) = default;
    AsciiGenerator& operator=(AsciiGenerator&&) = default;

    void Draw();

    void SetCharWidth(int char_width) { char_width_ = char_width; };
    void SetCharHeight(int char_height) { char_height_ = char_height; }
    void SetScaleFactor(float scale_factor) { scale_factor_ = scale_factor; }
    int GetCharWidth() const { return char_width_; }
    int GetCharHeight() const { return char_height_; }
    float GetScaleFactor() const { return scale_factor_; }

   private:
    static char GetChar(int value);
    void UpdateImage();

    float scale_factor_;
    int char_width_;
    int char_height_;
    cimg_library::CImg<unsigned int> image_;
};

}  // namespace asciigen

#endif
