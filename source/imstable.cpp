#include <fstream>
#include <sstream>
#include "spdlog/spdlog.h"
#include "FilePGM.h"
#include "ImageProcessor.h"

int main(int argc, char** argv) {
    spdlog::info("Welcome to imstable!");
    if(argc < 2)
    {
        spdlog::error("No input parameters!");
        return -1;
    }
    std::string path = argv[1];
    std::string path_out = "test.pgm";
    std::string line;
    std::stringstream ss;
    std::ifstream myfile (path);
    std::ofstream outfile (path_out);

    imstable::FilePGM newImage(path);
    imstable::ImageProcessor improcessor;
        // rotation
    std::vector<std::vector<int>> output_image;
    output_image.resize(newImage.height, std::vector<int>(newImage.width, 0));
    //output_image = rotate_CW_90(newImage.data,newImage.cols,newImage.rows);
    output_image = improcessor.RotateCW90(newImage);
    outfile << newImage.header_info.str();
    for(int row = 0; row < newImage.height; ++row)
    {
        for (int col = 0; col < newImage.width; ++col)
        {
            outfile << output_image[row][col];
            outfile << " ";
        } 
        outfile << "\n";   
    }
    outfile.close();
       // myfile.close();
    // }
    // else
    // {
    //     spdlog::error("Unable to open file");
    //     throw;
    // }
    return 0;
} 