#include "FilePGM.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <sstream>

namespace imstable{
    FilePGM::FilePGM(std::string path)
    {
        this->filePath = path;
        this->isOpen = true;
    }

	FilePGM::~FilePGM(void)
	{
        FilePGM::Close();
	}

    int FilePGM::Load()
    {
        this->MaxVal = 0;
        this->myfile.open(this->filePath);
        if (this->myfile.is_open())
        {
            spdlog::info(this->filePath);
            
            // First line, check file format
            FilePGM::GetFileFormat();

            // Second line : comment -> We assume that all files have a comment here
            FilePGM::GetFileComment();
            
            // Read height/width information
            FilePGM::GetFileDimensions();
            
            // Read MaxVal
            FilePGM::GetMaxValue();

            // Resize container to image dimensions
            this->data.resize(this->height, std::vector<int>(this->width, 0));
            
            // Get image data
            FilePGM::GetImageData();

            // Close file
            this->myfile.close();
            
            return 0;
        }
        else
        {
            spdlog::error("Unable to open file");
            throw;
        }
    }
    
    int FilePGM::Write()
    {
        std::ofstream outfile (this->filePath);

        // Write header
        outfile << this->header_info.str();

        // Write data
        for(int row = 0; row < this->height; ++row)
        {
            for (int col = 0; col < this->width; ++col)
            {
                outfile << this->data[row][col];
                outfile << " ";
            } 
            outfile << "\n";   
        }
        outfile.close();
        return 0;
    }

    int FilePGM::Close()
    {
        if(this->isOpen)
        {
            this->myfile.close();
            this->isOpen = false;
            return 0;
        }
        return 1;
    }

    void FilePGM::GetFileFormat()
    {
        std::string line;
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
    }

    void FilePGM::GetFileComment()
    {
        std::string line;
        std::getline(myfile,line);
        if(line.find('#') != std::string::npos)
        {
            spdlog::info("Comment: " + line);
        }
        this->header_info << line << "\n";
    }

    void FilePGM::GetFileDimensions()
    {
        this->ss << myfile.rdbuf();
        this->ss >> this->width >> this->height;
        this->header_info << this->width << " " << this->height << "\n";
        spdlog::info("Columns: " + std::to_string(this->width) + " Rows: " + std::to_string(this->height));
    }

    void FilePGM::GetMaxValue()
    {
        this->ss >> this->MaxVal;
        this->header_info << this->MaxVal << "\n";
        spdlog::info("Maxval: " + std::to_string(this->MaxVal));
    }

    void FilePGM::GetImageData()
    {
        for(int row = 0; row < this->height; ++row)
        {
            for (int col = 0; col < this->width; ++col)
            {
                ss >> this->data[row][col];
            }    
        }
    }
    
    void FilePGM::UpdateHeader()
    {   
        std::stringstream header;
        header << "P2" << "\n";
        header << "# image updated" << "\n";
        header << this->width << " " << this->height << "\n";
        this->MaxVal = 254;
        header << this->MaxVal << "\n";
        this->header_info << header.str();
    }
}