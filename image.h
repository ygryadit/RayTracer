#include "vector.h"
#include <fstream>

class ImageWriter
{
    std::ofstream out;
    int width_;
    int height_;
    
public: 
    ImageWriter(int width, int height, const char* file_name);
        
    void write(const Vec3& rgb);
    
    int width() const;
    int height() const;
};
