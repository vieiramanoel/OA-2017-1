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
    System(std::string file_name);
    void writeFile();
    ~System();
  private:
    VirtualHdd hdd;
    FatTable fat32;

    int calculateClusters();
    std::streampos calculateFileSize();

    std::ifstream file;
    std::string file_name;
    int hdd_cluster_size = hdd.getClusterSize();

};

#endif // SYSTEM_HPP
