#ifndef ImageProcessor_H
#define ImageProcessor_H

#include "ImageFrame.h"

namespace imstable
{
    class ImageProcessor
    {
        public:
        ImageProcessor();
        ~ImageProcessor();
        ImageFrame::ImageData_t RotateCW90(ImageFrame& image);
        ImageFrame::ImageData_t FlipHoriz(ImageFrame& image);
        ImageFrame::ImageData_t FlipVert(ImageFrame& image);
        //ImageFrame::ImageData_t RotateAngle(ImageFrame image, int angle);
        ImageFrame::ImageData_t RotateAngle(ImageFrame& image, double degree_angle, int pivot_x, int pivot_y, bool bilinear);
        int InterpolateBiliniar(ImageFrame& image, double x, double y);
        int RotateCCW90();
        private:
        bool saved;
    };
} // end namespace

#endif
