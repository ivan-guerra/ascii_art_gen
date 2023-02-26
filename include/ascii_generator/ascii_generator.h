#ifndef ASCII_GENERATOR_H_
#define ASCII_GENERATOR_H_

#include <boost/gil.hpp>
#include <string>

namespace asciigen {

class AsciiGenerator {
   public:
    static constexpr float kDefaultScaleFactor = 1.f;
    static const int kDefaultCharWidth = 10;
    static const int kDefaultCharHeight = 18;

    AsciiGenerator() = delete;
    AsciiGenerator(const std::string& filename,
                   float scale_factor = kDefaultScaleFactor,
                   int char_width = kDefaultCharWidth,
                   int char_height = kDefaultCharHeight);
    ~AsciiGenerator() = default;
    AsciiGenerator(const AsciiGenerator&) = default;
    AsciiGenerator& operator=(const AsciiGenerator&) = default;
    AsciiGenerator(AsciiGenerator&&) = default;
    AsciiGenerator& operator=(AsciiGenerator&&) = default;

    void Draw(const std::string& outfile);

    void SetCharWidth(int char_width) { char_width_ = char_width; };
    void SetCharHeight(int char_height) { char_height_ = char_height; }
    void SetScaleFactor(float scale_factor) { scale_factor_ = scale_factor; }
    int GetCharWidth() const { return char_width_; }
    int GetCharHeight() const { return char_height_; }
    float GetScaleFactor() const { return scale_factor_; }

   private:
    enum class ImageType {
        kUnknown,
        kPng,
        kJpg,
    };

    static char GetChar(int value);
    ImageType GetImageType(const std::string& filename) const;
    void UpdateImage();

    float scale_factor_;
    int char_width_;
    int char_height_;
    boost::gil::rgb8_image_t image_;
};

}  // namespace asciigen

#endif
