#include "system.hpp"
#include <iostream>

System::System()
{

}

System::~System(){
    if(file.is_open())
        file.close();
}

void System::setFile(std::string filename){
    file = std::ifstream(filename, std::ifstream::binary);
    file.seekg(0, std::ios::beg);
}

void System::writeFile(std::string filename){
    setFile(filename);
    auto clusters = calculateClusters();
    if(clusters == -1){
        return;
    }
    auto available_sector = hdd.getNextSector();
    file.seekg(0, std::ios::beg);
    fat32.addNewName(filename, available_sector);
    for(int cluster = 0; cluster < clusters; cluster++){
        auto sector = available_sector;
        for(int i = 0; i < hdd.getClusterSize(); i++, sector.sector_index++){
            char *buffer = new char[512];
            file.read(buffer, 511);
            int read = file.gcount();
            buffer[read] = '\0';
            if(read < 511)
                fat32.addName(sector, true);
            else
                fat32.addName(sector, false);
            std::cout << buffer << std::endl;

            hdd.write(buffer, sector);
            delete[] buffer;
        }
        available_sector = hdd.getNextTrack(available_sector);
    }


}

void System::readFile(std::string filename){
    auto pos = fat32.getPosition(filename);
    auto params = fat32.getSector(pos);
    std::ofstream extfile("saida.txt");
    do{
        std::string buffer = reinterpret_cast<char*>(hdd.getbuffer(params.sector));
        extfile << buffer;
        pos = params.next;
        if(pos != -1)
            params = fat32.getSector(pos);
    }while(pos != -1);
}


int System::calculateClusters(){
    auto filesize = calculateFileSize();
    int file = (int) (filesize);
    std::cout << file << std::endl;
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
