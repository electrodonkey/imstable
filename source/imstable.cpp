#include <fstream>
#include <sstream>
#include "spdlog/spdlog.h"
#include "FilePGM.h"

std::vector<std::vector<int>> rotate_CW_90(std::vector<std::vector<int>> input_image, int width, int height)
{
    std::vector<std::vector<int>> output_image;
    output_image.resize(height, std::vector<int>(width, 0));
    for (int row = 0; row < height; ++row) 
    {
        for (int col = 0; col < width; col+=1) 
        {
            output_image[col][width-1-row] = input_image[row][col];
        }
    }

    return output_image;
}

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
    int numcols = 0 , numrows = 0, row = 0, col = 0, maxval = 0;
    // if (myfile.is_open())
    // {
    //     // First line : version
    //     std::getline(myfile,line);
    //     if(line.compare("P2") != 0)
    //     {
    //         spdlog::error("Unexpected file type!");
    //         throw;
    //     }
    //     else
    //     { 
    //         spdlog::info("File version:" + line);
    //     }  
    //     // Second line : comment
    //     std::getline(myfile,line);
    //     spdlog::info("Comment: " + line);
    //     ss << myfile.rdbuf();
    //     ss >> numcols >> numrows;
    //     spdlog::info("Columns: " + std::to_string(numcols) + "Rows: " + std::to_string(numrows));
    //     std::vector<std::vector<int>> matrix;
    //     matrix.resize(numrows, std::vector<int>(numcols, 0));
    //     ss >> maxval;
    //     spdlog::info("Maxval: " + std::to_string(maxval));
    //     // Following lines : data
    //     for(row = 0; row < numrows; ++row)
    //     {
    //         for (col = 0; col < numcols; ++col)
    //         {
    //             ss >> matrix[row][col];
    //         }    
    //     }
        //spdlog::info("Test: " + std::to_string(matrix[5][5]));
        imstable::FilePGM newImage(path);
        // rotation
        std::vector<std::vector<int>> output_image;
        output_image.resize(numrows, std::vector<int>(newImage.cols, 0));
        output_image = rotate_CW_90(newImage.data,newImage.cols,newImage.rows);
        for(row = 0; row < newImage.rows; ++row)
        {
            for (col = 0; col < newImage.cols; ++col)
            {
                outfile << output_image[row][col];
                outfile << " ";
            }    
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