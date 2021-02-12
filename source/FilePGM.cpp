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
            // First line: format
            std::getline(myfile,line);
            if(line.compare("P2") != 0)
            {
                spdlog::error("Unexpected file type!");
                throw;
            }
            else
            { 
                spdlog::info("File version:" + line);
            }  
            
            // Second line : comment -> We assume that all files have a comment here
            std::getline(myfile,line);
            if(line.find('#') != std::string::npos)
            {
                spdlog::info("Comment: " + line);
            }
            ss << myfile.rdbuf();
            ss >> this->cols >> this->rows;
            spdlog::info("Columns: " + std::to_string(this->cols) + " Rows: " + std::to_string(this->rows));
            this->data.resize(this->rows, std::vector<int>(this->cols, 0));
            ss >> MaxVal;
            spdlog::info("Maxval: " + std::to_string(MaxVal));
            for(int row = 0; row < this->rows; ++row)
            {
                for (int col = 0; col < this->cols; ++col)
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