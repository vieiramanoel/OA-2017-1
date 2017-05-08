#ifndef SYSTEM_HPP
#define SYSTEM_HPP


#include "virtualhdd.hpp"
#include "fattable.hpp"
#include <string>
#include <fstream>
#include <cmath>

class System
{
  public:
    System(std::string filename);
    void writeFile();
    ~System();
  private:
    VirtualHdd hdd;
    FatTable fat32;

    int calculateClusters();
    std::streampos calculateFileSize();

    std::ifstream file;
    std::string filename;
    int hdd_sector_size = hdd.getSectorSize();

};

#endif // SYSTEM_HPP
