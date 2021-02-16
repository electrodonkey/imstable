#include "ImageProcessor.h"
#include <math.h>

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

    ImageFrame::ImageData_t ImageProcessor::FlipHoriz(ImageFrame image)
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

    ImageFrame::ImageData_t ImageProcessor::FlipVert(ImageFrame image)
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
        x = width, y = heigth, m,n - coordinates of pivot point
        X=x·cos(θ)−y·sin(θ)−m·cos(theta) +n·sin(θ) +m
        Y=y·cos(θ) +x·sin(θ)−m·sin(theta)−n·sin(θ) +n

    */
    ImageFrame::ImageData_t ImageProcessor::RotateAngle(ImageFrame image, int angle)
    {
        ImageFrame::ImageData_t output_image_data;
        output_image_data.resize(image.height, std::vector<int>(image.width, 0));
        int hwidth = image.width / 2;
		int hheight = image.height / 2;
        double sinma = sin(-angle);
		double cosma = cos(-angle);
        for (int x = 0; x < image.width; x++) 
        {
            for (int y = 0; y < image.height; y++) 
            {
                int xt = x - hwidth;
		        int yt = y - hheight;
		
		        int xs = (int)round((cosma * xt - sinma * yt) + hwidth);
		        int ys = (int)round((sinma * xt + cosma * yt) + hheight);

		        if(xs >= 0 && xs < image.width && ys >= 0 && ys < image.height) 
                {
			        /* set target pixel (x,y) to color at (xs,ys) */
                    output_image_data[x,y]=image.data[xs,ys];
		        } 
                else 
                {
			        /* set target pixel (x,y) to some default background */
                    output_image_data[x,y].push_back(0);
		        }
            }
        }
        return output_image_data;
    }
} // end namespace