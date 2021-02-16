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
        Bilinear Interpolation:
        Bi-linear interpolation finds values between pixels in two directions

        gray(P1) = (1−x)·gray(floor(x),floor(y)) +x·gray(ceiling(x),floor(y))
        gray(P2) = (1−x)·gray(floor(x),ceiling(y))+x·gray(ceiling(x),ceiling(y))
        gray(P3) = (1−y)·gray(P1) +y·gray(P2)

        int bilinear_interpolate(the_image, x, y, rows, cols)
        {
            if(x < 0.0 || x >= (double)(cols-1) || y < 0.0 || y >= (double)(rows-1)) return(0);
            mp_double = floor(x);
            floor_x = tmp_double;
            tmp_double = floor(y);
            floor_y = tmp_double;
            tmp_double = ceil(x);
            ceil_x = tmp_double;
            tmp_double = ceil(y);
            ceil_y = tmp_double;
            fraction_x = x - floor(x);
            fraction_y = y - floor(y);
            one_minus_x = 1.0 - fraction_x;
            one_minus_y = 1.0 - fraction_y;
            tmp_double = one_minus_x *(double)(the_image[floor_y][floor_x]) +fraction_x *(double)(the_image[floor_y][ceil_x]);
            p1 = tmp_double;tmp_double = one_minus_x *(double)(the_image[ceil_y][floor_x]) +fraction_x *(double)(the_image[ceil_y][ceil_x]);
            p2 = tmp_double;tmp_double = one_minus_y * (double)(p1) +fraction_y * (double)(p2);
            p3 = tmp_double;
            return(p3);
        }
    */

    /*
        x = width, y = heigth, m,n - coordinates of pivot point
        X=x·cos(θ)−y·sin(θ)−m·cos(theta) +n·sin(θ) +m
        Y=y·cos(θ) +x·sin(θ)−m·sin(theta)−n·sin(θ) +n

        arotate(the_image, out_image,angle,m, n, bilinear,rows, cols)
        {

            // the following magic number is from180 degrees divided by pi 
            radian_angle = angle/57.29577951;
            cosa  = cos(radian_angle);
            sina  = sin(radian_angle);/
            
            for(i=0; i<rows; i++)
            {
                for(j=0; j<cols; j++)
                {
                    tmpx = (double)(j)*cosa-(double)(i)*sina-(double)(m)*cosa+(double)(m)+(double)(n)*sina;
                    tmpy = (double)(i)*cosa+(double)(j)*sina-(double)(m)*sina-(double)(n)*cosa+(double)(n);
                    new_j = tmpx;
                    new_i = tmpy;
                    if(bilinear == 0)
                    {
                        if(new_j < 0||new_j >= cols ||new_i < 0 ||new_i >= rows)
                            out_image[i][j] = FILL;
                            else
                            out_image[i][j] =the_image[new_i][new_j];
                    }  
                    else
                    {
                        out_image[i][j] =bilinear_interpolate(the_image,tmpx, tmpy,rows, cols);
                    }  // ends bilinear if 
            
                }  // ends loop over j 
            
            }  // ends loop over i 
        }

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