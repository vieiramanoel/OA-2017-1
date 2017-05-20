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
    if(clusters == -1)
        return;
    auto available_sector = hdd.getNextSector();
    fat32.addName(file_name, available_sector);

    file.seekg(0, std::ios::beg);
    for(int cluster = clusters; cluster > 0; cluster--){
        for(int i = 0; i < hdd.getClusterSize(); i++){

            char *buffer = new char[512];

            if(file){
                file.read(buffer, 512);

                if (file){
                    if(!file.eof())
                        file.seekg(0, std::ios::cur);
                }
            }
            else if(!file.eof()){
                std::cout << "file error" << std::endl;
                return;
            }

            hdd.write(buffer, available_sector);

//            do{
//                available_sector.track_index++;
//            }while(!available_sector);
// erro na logica do setor disponivel
            delete[] buffer;
        }
    }


}

int System::calculateClusters(){
    auto filesize = calculateFileSize();
    int file = (int) filesize;
    if(file == -1)
        return -1;
    auto clusters = ceil(file/hdd_cluster_size);
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
