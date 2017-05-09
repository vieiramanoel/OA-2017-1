#include "system.hpp"
#include <iostream>
System::System(std::string filename)
{
    file_name = filename;
}

System::~System(){
    if(file.is_open())
        file.close();
}

void System::writeFile(){

    auto clusters = calculateClusters();
    if(clusters == -1)
        return;
    auto available_sector = hdd.getNextSector();
    fat32.addName(file_name, available_sector);
    file.open(file_name, std::ios::in);
    char *buffer = new char[512];
//    file.read(buffer, 4);
//    buffer[5] = '\0';
    std::cout << buffer << std::endl;
    if (file)
        std::cout << "all characters read successfully.";
    else
        std::cout << "error: only " << file.gcount() << " could be read";
    file.close();
//    for(int cluster = clusters; cluster > 0; cluster--){
//        for(int i = 0; i < hdd.getClusterSize(); i++){
//            //file.read(buffer, 512);
//            file.getline(buffer, 512);
//            file.seekg(0, std::ios::beg);
//            std::cout << buffer << std::endl;
//            hdd.write(buffer, available_sector);
//            do{
//                available_sector.track_index++;
//            }while(!available_sector);
//        }
//    }

    delete[] buffer;
}

int System::calculateClusters(){
    auto filesize = calculateFileSize();
    std::cout << filesize << std::endl;
    int file = (int) filesize;
    if(file == -1)
        return -1;
    auto clusters = ceil(file/hdd_cluster_size);
    return clusters;
}

std::streampos System::calculateFileSize(){
    file.open(file_name, std::ifstream::binary);
    if(file.is_open()){
        auto begin = file.tellg();
        file.seekg(0, std::ios::end);
        auto end = file.tellg();
        return end-begin;
    }
    else
        std::cout << "could not open file" << std::endl;
    file.close();
    return std::streampos(-1);
}
