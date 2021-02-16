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
        void UpdateHeader();
        
        private:
        std::stringstream ss;
        std::ifstream myfile;
        int MaxVal;
        void GetFileFormat();
        void GetFileComment();
        void GetFileDimensions();
        void GetMaxValue();
        void GetImageData();
        bool isOpen = false;
    };
} // namespace imstable

#endif
