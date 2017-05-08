#include "virtualhdd.hpp"
#include <iostream>
VirtualHdd::VirtualHdd()
{
   cylinder = new track_array[cylinderamount];
   std::cout << "constructed" << std::endl;
}

VirtualHdd::~VirtualHdd(){
    delete[] cylinder;
}


int VirtualHdd::getSectorSize(){
    return sector_size;
}

int VirtualHdd::getNextSector()
{
    int next = 0;
//    for(auto i = 0; i < cylinderamount; i++){
//        for(auto j = 0; j < 5; i++){
//            for(auto k = 0; k < 60; k++){
//                for(auto l = 0; l < 512; l++){
//                    unsigned int value = cylinder[i].track[j].sector[k].bytes_s[l];
//                    if(value == 0)
//                        break;
//                    std::cout << "here " << value << std::endl;
//                    std::getchar();

//                }
//            }
//        }
//    }
    return 0;
}
