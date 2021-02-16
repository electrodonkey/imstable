#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"
#include "FilePGM.h"
#include "ImageProcessor.h"

char* getCmdOption(char ** begin, char ** end, const std::string& option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

void printHelp()
{
    std::cout << "Imstable usage: \n";
    std::cout << "\t ./imstable_demo -f INPUT_FILE -o OPERATION \n";
    std::cout << "\t\t INPUT_FILE can be: PGMA (check assets dir for some examples) \n";
    std::cout << "\t OPERATION can be: \n";
    std::cout << "\t\t rotate -a ANGLE \n";
    std::cout << "\t ./imstable_demo -h : prints this message\n";
}

int main(int argc, char * argv[])
{
    std::string output_image_path = "output.pgm";
    std::string test_image_path = "output_image.pgm";
    
    if(argc < 2)
    {
        printHelp();
        return 0;  
    }

    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        printHelp();
        return 0;
    }

    if(cmdOptionExists(argv, argv+argc, "-f"))
    {
        char * filename = getCmdOption(argv, argv+argc, "-f");

        if (filename)
        {   
            spdlog::info("Loading file");
            std::string input_image_path = filename;
            imstable::FilePGM oldImage(input_image_path);
            imstable::FilePGM newImage(output_image_path);
            imstable::ImageProcessor improcessor;

            oldImage.Load();

            newImage.height = oldImage.height;
            newImage.width = oldImage.width;
            newImage.header_info << oldImage.header_info.str();
            newImage.data.resize(oldImage.height, std::vector<int>(oldImage.width, 0));

            char * option = getCmdOption(argv, argv+argc, "-o");
            if(!(option == "rotate"))
            {   
                spdlog::info("Image rotate & crop");
                char * angle = getCmdOption(argv, argv + argc, "-a");
                char * crop_start_x = getCmdOption(argv, argv + argc, "-cx");
                char * crop_start_y = getCmdOption(argv, argv + argc, "-cy");
                char * crop_height = getCmdOption(argv, argv + argc, "-ch");
                char * crop_width = getCmdOption(argv, argv + argc, "-cw");
                if(angle && crop_start_x && crop_start_y && crop_height && crop_width)
                {
                    double rotation_angle = std::stod(angle);
                    int crop_x = std::stoi(crop_start_x);
                    int crop_y = std::stoi(crop_start_y);
                    int crop_h = std::stoi(crop_height);
                    int crop_w = std::stoi(crop_width);

                    newImage.data = improcessor.RotateAngle(oldImage, rotation_angle, oldImage.height/2, oldImage.width/2, true);

                    imstable::FilePGM rotImage(test_image_path);
                    rotImage.height = crop_h;
                    rotImage.width = crop_w;
                    rotImage.UpdateHeader();
                    rotImage.data.resize(crop_h, std::vector<int>(crop_w, 0));
                    rotImage.data = improcessor.CropImage(newImage, crop_x, crop_y, crop_h, crop_w);
                    //newImage.Write();
                    rotImage.Write();
                }
                else
                {
                    spdlog::error("Image rotate & crop, missing parameter");
                }
            }
        }
    }
    return 0;
}