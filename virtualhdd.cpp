#include "virtualhdd.hpp"
#include <string.h>
#include <iostream>
VirtualHdd::VirtualHdd()
{
   cylinder = new track_array[cylinder_amount];
}

VirtualHdd::~VirtualHdd(){
    delete[] cylinder;
}


int VirtualHdd::getClusterSize(){
    return cluster_size;
}

availablesector VirtualHdd::getNextSector()
{
    for(int track = 0; track < TRACKSIZE; track++){
        for(int cylin = 0; cylin < cylinder_amount; cylin++){
            for(int cluster = 0; cluster < SECTORSIZE; cluster+=4){
                auto sector = cluster*cluster_size;
                if(cylinder[cylin].isClusterAvailable(track, sector))
                    return availablesector(cylin, track, sector);
            }
        }
    }

    return availablesector();
}

void VirtualHdd::write(char *buffer, availablesector sector)
{
    unsigned char* sec_buffer = getbuffer(sector);
    for(int i = 0; i < 512; i++){
        sec_buffer[i] = (unsigned char) buffer[i];
    }
    std::cout << sec_buffer << std::endl;
    getchar();

}

unsigned char* VirtualHdd::getbuffer(availablesector sector)
{
    return (unsigned char*) cylinder[sector.cylinder_index].track[sector.track_index].sector[sector.sector_index].bytes_s;
}


