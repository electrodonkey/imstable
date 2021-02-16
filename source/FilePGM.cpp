#include "FilePGM.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <sstream>

namespace imstable{
    FilePGM::FilePGM(std::string path)
    {
        this->filePath = path;
        FilePGM::Load(this->filePath);
        this->isOpen = true;
    }

	FilePGM::~FilePGM(void)
	{
        FilePGM::Close();
	}

    int FilePGM::Load(std::string filePath)
    {
        std::string line;
        std::stringstream ss;
        int MaxVal = 0;

        this->myfile.open(filePath);
        if (this->myfile.is_open())
        {
            spdlog::info(filePath);
            // First line, check file format
            std::getline(myfile,line);
            if(line.compare("P2") != 0)
            {
                spdlog::error("Unexpected file type!");
                throw;
            }
            else
            { 
                this->header_info << line << "\n";
                spdlog::info("File version:" + line);
            }  
            
            // Second line : comment -> We assume that all files have a comment here
            std::getline(myfile,line);
            if(line.find('#') != std::string::npos)
            {
                spdlog::info("Comment: " + line);
            }
            this->header_info << line << "\n";
            
            // Read height/width information
            ss << myfile.rdbuf();
            ss >> this->width >> this->height;
            this->header_info << this->width << " " << this->height << "\n";
            spdlog::info("Columns: " + std::to_string(this->width) + " Rows: " + std::to_string(this->height));
            
            // Read MaxVal
            ss >> MaxVal;
            this->header_info << MaxVal << "\n";
            spdlog::info("Maxval: " + std::to_string(MaxVal));

            // Resize container to image dimensions
            this->data.resize(this->height, std::vector<int>(this->width, 0));
            
            for(int row = 0; row < this->height; ++row)
            {
                for (int col = 0; col < this->width; ++col)
                {
                    ss >> this->data[row][col];
                }    
            }
            return 0;
        }
        else
        {
            spdlog::error("Unable to open file");
            throw;
        }
    }
    int FilePGM::Close()
    {
        if(this->isOpen)
        {
            this->myfile.close();
            this->isOpen = false;
            return 0;
        }
        else
        {
            return 1;
        }
    }
}