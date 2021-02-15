#ifndef ImageFrame_H
#define ImageFrame_H

#include <vector>

namespace imstable
{
    class ImageFrame
    {
        public:
        ImageFrame();
        ~ImageFrame();
        typedef std::vector<std::vector<int>> ImageData_t;
        ImageData_t data;
        int width;
        int height;
    };
} // end namespace

#endif