#include "system.hpp"
#include <iostream>

System::System(std::string filename)
{
    file_name = filename;
    file = std::ifstream(filename, std::ifstream::binary);
    file.seekg(0, std::ios::beg);
}

System::~System(){
    if(file.is_open())
        file.close();
}

void System::writeFile(){

    auto clusters = calculateClusters();
    if(clusters == -1){
        return;
    }
    auto available_sector = hdd.getNextSector();
    file.seekg(0, std::ios::beg);
    fat32.addNewName(file_name, available_sector);
    for(int cluster = 0; cluster < clusters; cluster++){
        auto sector = available_sector;
        bool iseof{false};
        for(int i = 0; i < hdd.getClusterSize(); i++, sector.sector_index++){
            char *buffer = new char[512];

            if(file){
                file.read(buffer, 512);
            }
            else if(!file.eof()){
                std::cout << "file error" << std::endl;
                delete[] buffer;
                return;
            }
            else{
                if(file.eof()){
                     //std::cout << "EOF reached" << std::endl;
                     //You can uncomment the line above to check if EOF was hit
                     buffer[0] = '\0';
                     iseof = true;
                     //here is necessary to add a \0 to every cluster's sector to identify
                     //if it's being used in this case as an EOF
                }
            }

            hdd.write(buffer, sector);
            fat32.addName(sector, iseof);
            delete[] buffer;
        }
        available_sector = hdd.getNextTrack(available_sector);
        //need split FAT insertion in two functions
        //fat32.addName(file_name, available_sector, iseof);
    }


}

int System::calculateClusters(){
    auto filesize = calculateFileSize();
    int file = (int) (filesize);
    if(file == -1)
        return -1;
    auto clusters = ceil( ( (float)file/(512*4) ) );
    return clusters;
}

std::streampos System::calculateFileSize(){
    if(file){
        file.seekg(0, std::ios::beg);
        auto begin = file.tellg();
        file.seekg(0, std::ios::end);
        auto end = file.tellg();
       return end-begin;
    }
    else
        std::cout << "file error at calculate file size" << std::endl;

    return std::streampos(-1);
}
