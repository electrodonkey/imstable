#ifndef FilePGM_H
#define FilePGM_H

#include <fstream>
#include <vector>
#include "ImageFrame.h"

namespace imstable{
    class FilePGM : public ImageFrame
    {
        public:
        FilePGM(std::string fileName); // create array based on file with this name
        ~FilePGM(void);
        std::string filePath;
        int Load(std::string fileName);
        int Close();
        //int height;
        //int width;
        //std::vector<std::vector<int>> data;
        
        private:
        std::ifstream myfile;
        bool isOpen = false;
    };
} // namespace imstable

#endif
