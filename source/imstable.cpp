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
        //print_help();
        return -1;
    }

    std::string input_image_path = argv[1];
    std::string output_image_path = "test.pgm";

    imstable::FilePGM oldImage(input_image_path);
    imstable::FilePGM newImage(output_image_path);
    imstable::ImageProcessor improcessor;
    
    // load an existing image
    oldImage.Load();

    // prepare a new image shell to receive the transformed image
    newImage.height = oldImage.height;
    newImage.width = oldImage.width;
    newImage.header_info << oldImage.header_info.str();
    newImage.data.resize(oldImage.height, std::vector<int>(oldImage.width, 0));

    // perform image transform
    //newImage.data = improcessor.RotateCW90(oldImage);
    //newImage.data = improcessor.RotateAngle(oldImage, 30);
    //newImage.data = improcessor.FlipHoriz(oldImage);
    newImage.data = improcessor.FlipVert(oldImage);
    // commit new image
    newImage.Write();
   
    return 0;
} 