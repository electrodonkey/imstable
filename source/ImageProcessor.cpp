#include "ImageProcessor.h"
#include <math.h>

namespace imstable
{
    ImageProcessor::ImageProcessor() = default;

    ImageProcessor::~ImageProcessor() = default;

    ImageFrame::ImageData_t ImageProcessor::RotateCW90(ImageFrame& image)
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

    ImageFrame::ImageData_t ImageProcessor::FlipHoriz(ImageFrame& image)
    {
        ImageFrame::ImageData_t output_image_data;
        output_image_data.resize(image.height, std::vector<int>(image.width, 0));
        for (int row = 0; row < image.height; ++row) 
        {
            for (int col = 0; col < image.width; col+=1) 
            {
                output_image_data[row][col] = image.data[image.height-1-row][col];
            }
        }

        return output_image_data;
    }

    ImageFrame::ImageData_t ImageProcessor::FlipVert(ImageFrame& image)
    {
        ImageFrame::ImageData_t output_image_data;
        output_image_data.resize(image.height, std::vector<int>(image.width, 0));
        for (int row = 0; row < image.height; ++row) 
        {
            for (int col = 0; col < image.width; col+=1) 
            {
                output_image_data[row][col] = image.data[row][image.width-1-col];
            }
        }

        return output_image_data;
    }
    /*
        Bilinear Interpolation:
        Bi-linear interpolation finds values between pixels in two directions

        gray(P1) = (1−x)·gray(floor(x),floor(y)) +x·gray(ceiling(x),floor(y))
        gray(P2) = (1−x)·gray(floor(x),ceiling(y))+x·gray(ceiling(x),ceiling(y))
        gray(P3) = (1−y)·gray(P1) +y·gray(P2)
    */
    int ImageProcessor::InterpolateBiliniar(ImageFrame& image, double x, double y)
    {
        if(x < 0.0 || x >= (float)(image.width-1) || y < 0.0 || y >= (float)(image.height-1)) 
        {
            return 0;
        }
        int floor_x = floor(x);
        int floor_y = floor(y);
        int ceil_x = ceil(x);
        int ceil_y = ceil(y);
        float fraction_x = x - floor_x;
        float fraction_y = y - floor_y;
        float one_minus_x = 1.0 - fraction_x;
        float one_minus_y = 1.0 - fraction_y;
        float p1 = one_minus_x * (float)(image.data[floor_y][floor_x]) + fraction_x * (float)(image.data[floor_y][ceil_x]);
        float p2 = one_minus_x * (float)(image.data[ceil_y][floor_x]) + fraction_x * (float)(image.data[ceil_y][ceil_x]);
        float p3 = one_minus_y * (float)(p1) +fraction_y * (float)(p2);
        return p3;
    }

   /**
    * @brief 
    *   Rotate an image with a given angle and a given pivot point
    *   x = width, y = heigth, m,n - coordinates of pivot point
    *   X=x·cos(θ)−y·sin(θ)−m·cos(theta) +n·sin(θ) +m
    *   Y=y·cos(θ) +x·sin(θ)−m·sin(theta)−n·sin(θ) +n
    * @param image Input image
    * @param degree_angle Angle in degrees -> + means CW rotation, - means CCW
    * @param pivot_x X coordinate of pivot point
    * @param pivot_y Y coordinate of pivot point
    * @param bilinear Use interpolation: False = no interpolation, True = use bilinear interpolation
    * @return ImageFrame::ImageData_t 
    */
    ImageFrame::ImageData_t ImageProcessor::RotateAngle(ImageFrame& image, double degree_angle, int pivot_x, int pivot_y, bool bilinear)
    {
        ImageFrame::ImageData_t output_image_data;
        output_image_data.resize(image.height, std::vector<int>(image.width, 0));
        
        // the following magic number is from180 degrees divided by pi 
        double radian_angle = degree_angle/57.29577951;
        
        double cosa  = cos(radian_angle);
        double sina  = sin(radian_angle);
        
        for(int i=0; i<image.height; i++)
        {
            for(int j=0; j<image.width; j++)
            {
                double new_j = (double)(j)*cosa-(double)(i)*sina-(double)(pivot_x)*cosa+(double)(pivot_x)+(double)(pivot_y)*sina;
                double new_i = (double)(i)*cosa+(double)(j)*sina-(double)(pivot_x)*sina-(double)(pivot_y)*cosa+(double)(pivot_y);

                if(bilinear == 0)
                {
                    if(new_j < 0 || new_j >= image.width ||new_i < 0 ||new_i >= image.height)
                    {
                        output_image_data[i][j] = 0;
                    }
                    else
                    {
                        output_image_data[i][j] = image.data[new_i][new_j];
                    }
                }  
                else
                {
                    output_image_data[i][j] = ImageProcessor::InterpolateBiliniar(image, new_j, new_i);
                }
            }
        }  
        return output_image_data;
    }
} // end namespace