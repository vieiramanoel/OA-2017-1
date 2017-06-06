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
    System();
    ~System();
    void readFile(std::string filename);
    void writeFile(std::string filename);
private:
    VirtualHdd hdd;
    FatTable fat32;

    int calculateClusters();
    std::streampos calculateFileSize();

    std::ifstream file;
    int hdd_cluster_size = hdd.getClusterSize();

    void setFile(std::string filename);
};

#endif // SYSTEM_HPP
