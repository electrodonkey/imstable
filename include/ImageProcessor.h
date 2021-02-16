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
        ImageFrame::ImageData_t RotateCCW90(ImageFrame& image);
        ImageFrame::ImageData_t FlipHoriz(ImageFrame& image);
        ImageFrame::ImageData_t FlipVert(ImageFrame& image);
        ImageFrame::ImageData_t RotateAngle(ImageFrame& image, double degree_angle, int pivot_x, int pivot_y, bool bilinear);
        ImageFrame::ImageData_t CropImage(ImageFrame& image, int crop_start_x, int crop_start_y, int crop_height, int crop_width);
        private:
        int InterpolateBiliniar(ImageFrame& image, double x, double y);
        bool saved;
    };
} // end namespace

#endif
