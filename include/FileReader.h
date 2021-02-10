#include <fstream>

namespace imstable{
class FileReader
{
public:
	FileReader(char *fileName); // create array based on file with this name
	~FileReader(void);
	std::string getType();
	struct timeval getTime();
	virtual std::string getDescription()=0;
    int FileOpen(void);
private:
	std::string m_type;
};
} // namespace imstable