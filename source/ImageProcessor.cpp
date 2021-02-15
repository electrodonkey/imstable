#include "ImageProcessor.h"
//#include "ImageFrame.h"

namespace imstable
{
    ImageProcessor::ImageProcessor() = default;

    ImageProcessor::~ImageProcessor() = default;

    ImageFrame::ImageData_t ImageProcessor::RotateCW90(ImageFrame image)
    {
        ImageFrame::ImageData_t output_image_data;
        output_image_data.resize(image.height, std::vector<int>(image.width, 0));
        for (int row = 0; row < image.height; ++row) 
        {
            for (int col = 0; col < image.width; col+=1) 
            {
                output_image_data[col][image.width-1-row] = image.data[row][col];
            }
        }

        return output_image_data;
    }

    int ImageProcessor::RotateCCW90()
    {
        return 0;
    }
} // end namespace