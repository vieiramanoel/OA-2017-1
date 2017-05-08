#include "system.hpp"
#include <iostream>
System::System(std::string filename)
{
    this->filename = filename;
}

System::~System(){
    file.close();
}

void System::writeFile(){

    auto clusters = calculateClusters();
    auto sectors = clusters * hdd_sector_size;
    auto nextsector = hdd.getNextSector();
    //std::cout << sectors << "lala" << nextsector << std::endl;
}

int System::calculateClusters(){
    auto filesize = calculateFileSize();
    int file = (int) filesize;
    auto clusters = ceil(file/hdd_sector_size);
    return clusters;
}

std::streampos System::calculateFileSize(){
    file.open(filename, std::ifstream::binary);
    if(file.is_open()){
        auto begin = file.tellg();
        file.seekg(0, std::ios::end);
        auto end = file.tellg();
        std::cout << begin-end << std::endl;
        return begin-end;
    }
    return -1;
}
