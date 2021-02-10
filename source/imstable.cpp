#include <fstream>
#include "spdlog/spdlog.h"

int main(int argc, char** argv) {
  spdlog::info("Welcome to imstable!");
  if(argc < 2)
  {
    spdlog::error("No input parameters!");
    return -1;
  }
  std::string path = argv[1];
  std::string line;
  std::ifstream myfile (path);
  if (myfile.is_open())
  {
    // First line : version
    std::getline(myfile,line);
    if(line.compare("P2") != 0)
    {
      spdlog::error("Unexpected file type!");
      throw;
    }
    else
    { 
      spdlog::info("File version:"+line);
    }  
      // Second line : comment
      std::getline(myfile,line);
      spdlog::info("Comment: "+line);

    // while ( getline (myfile,line) )
    // {
    //   std::cout << line << '\n';
    // }
    myfile.close();
  }
  else
  {
    spdlog::error("Unable to open file");
    throw;
  }
  return 0;
} 