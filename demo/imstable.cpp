#include <fstream>
#include <sstream>
#include <iostream>
#include "spdlog/spdlog.h"
#include "FilePGM.h"
#include "ImageProcessor.h"

char* getCmdOption(char ** begin, char ** end, const std::string & option)
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
        char * filename = getCmdOption(argv, argv + argc, "-f");

        if (filename)
        {
            std::string input_image_path = filename;
            imstable::FilePGM oldImage(input_image_path);
            imstable::FilePGM newImage(output_image_path);
            imstable::ImageProcessor improcessor;

            oldImage.Load();

            newImage.height = oldImage.height;
            newImage.width = oldImage.width;
            newImage.header_info << oldImage.header_info.str();
            newImage.data.resize(oldImage.height, std::vector<int>(oldImage.width, 0));

            char * option = getCmdOption(argv, argv + argc, "-o");
            if(option == "rotate")
            {
                char * angle = getCmdOption(argv, argv + argc, "-a");
                if(angle)
                {
                    double rotation_angle = std::stod(angle);
                    newImage.data = improcessor.RotateAngle(oldImage, rotation_angle, oldImage.height/2, oldImage.width/2, true);
                    newImage.Write();
                }
            }
        }
    }
    return 0;
}