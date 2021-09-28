#include <stdexcept>
#include "image.h"

ImageWriter::ImageWriter(int width, int height, const char* file_name)
    : out(file_name), width_(width), height_(height)
{
    if (!out)
        throw std::runtime_error("Unable to open file for writing");
    out << "P6\n" << width << ' ' << height << " 255\n";
}

static double clamp(double x)
{
    if (x < 0) return 0;
    if (x > 255.0) return 255.0;
    return x;
}

void ImageWriter::write(const Vec3& rgb)
{
    unsigned char bytes[3] = {
        clamp(rgb[0] * 255.0),
        clamp(rgb[1] * 255.0),
        clamp(rgb[2] * 255.0)
    };
    out.write((const char*)bytes, 3);
}

int ImageWriter::width() const
{
    return width_;
}

int ImageWriter::height() const
{
    return height_;
}
