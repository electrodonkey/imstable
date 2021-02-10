#include <fstream>

#include "FileReader.h"



namespace imstable{

	FileReader::FileReader(char *fileName)
	{
		std::ifstream infile(fileName);
	}
	FileReader::~FileReader(void)
	{

	}
	int FileReader::FileOpen(void)
	{
		return 0;
	}

} // namespace imstable