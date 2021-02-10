#include <iostream>
#include <fstream>
#include "spdlog/spdlog.h"

int main() {
  std::cout << "Hello World!\n";
  spdlog::info("Welcome to spdlog!");
  std::string path = "assets//lena.ascii.pgm";
  std::string line;
  std::ifstream myfile (path);
  if (myfile.is_open())
  {
    // First line : version
    std::getline(myfile,line);
    if(line.compare("P2") != 0)
    {
      std::cerr << "Version error" << std::endl;
    }
    else
    { 
      std::cout << "Version : " << line << std::endl;
    }
    // while ( getline (myfile,line) )
    // {
    //   std::cout << line << '\n';
    // }
    myfile.close();
  }
  else std::cout << "Unable to open file"; 
  return 0;
} 