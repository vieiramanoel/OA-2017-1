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
            for(int cluster = 0; cluster < SECTORSIZE; cluster++){
                auto sector = cluster*cluster_size;
                if(cylinder[cylin].isClusterAvailable(track, sector))
                {
                    //if you wanna know what indices were found, simply print what's been returned with a cout
                    return availablesector(cylin, track, sector);
                }
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
//    std::cout << "saved buff: " << sec_buffer << std::endl;
//    std::cout << "at " << sector << std::endl;
}
availablesector VirtualHdd::getNextTrack(availablesector currsector)
{

    while(!cylinder[currsector.cylinder_index].isClusterAvailable(currsector.track_index, currsector.sector_index)){
        if(currsector.track_index == 4){
            currsector = this->getNextSector();
        }else{
            currsector.track_index++;
        }
    }
    return currsector;
}

unsigned char* VirtualHdd::getbuffer(availablesector sector)
{
    return (unsigned char*) cylinder[sector.cylinder_index].track[sector.track_index].sector[sector.sector_index].bytes_s;
}


