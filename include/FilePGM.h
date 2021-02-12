#include <fstream>
#include <vector>

namespace imstable{
class FilePGM
{
public:
	FilePGM(std::string fileName); // create array based on file with this name
	~FilePGM(void);
    std::string filePath;
    int Load(std::string fileName);
    int Close();
    int rows;
    int cols;
    std::vector<std::vector<int>> data;
private:
    std::ifstream myfile;
    bool isOpen = false;
};
} // namespace imstable