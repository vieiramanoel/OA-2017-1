#ifndef SYSTEM_HPP
#define SYSTEM_HPP


#include "virtualhdd.hpp"
#include "fattable.hpp"
#include <string>
#include <fstream>
#include <cmath>
/* Class definition for our system (something like kernel, or file manager)
 * interfaces fat table (virtual) and HDD (physical) having access to both classes
 */
class System
{
  public:
    System();
    ~System();
    bool readFile(std::string filename);
    bool writeFile(std::string filename);
    void printSizeTable();
    bool removeFatItem(std::string filename);
    int getTime(std::string filename);
private:
    VirtualHdd hdd;
    FatTable fat32;

    int calculateClusters();
    std::streampos calculateFileSize();

    std::ifstream file;
    int hdd_cluster_size = hdd.getClusterSize();
    int filesize;
    void setFile(std::string filename);
};

#endif // SYSTEM_HPP
