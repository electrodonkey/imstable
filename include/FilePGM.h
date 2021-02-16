#ifndef FilePGM_H
#define FilePGM_H
#include <sstream>
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
        std::stringstream header_info;
        
        int Load();
        int Close();
        int Write();
        //int height;
        //int width;
        //std::vector<std::vector<int>> data;
        
        private:
        std::ifstream myfile;
        bool isOpen = false;
    };
} // namespace imstable

#endif
