#ifndef BLOCKDEFINITIONS_HPP
#define BLOCKDEFINITIONS_HPP

#define TRACKSIZE 5
#define SECTORSIZE 60
#define CLUSTEZSIZE 4
#include <iostream>
#include <ostream>
struct block{
    unsigned char bytes_s[512];
    block(){
        for(auto i = 0; i < 512; i++)
            bytes_s[i] = (unsigned char) 0;
    }
};

struct sector_array{
    block sector[SECTORSIZE];
};

struct track_array{
    sector_array track[TRACKSIZE];
    bool isClusterAvailable(int track_, int sector_){
        if(sector_ > SECTORSIZE - CLUSTEZSIZE)
            return false;
        for(int i = sector_; i < sector_+CLUSTEZSIZE; i++){
            if(track[track_].sector[i].bytes_s[0] != (unsigned char) 0)
            {
                //return if cluster isn't available
                return false;
            }
        }
        return true;
    }
};

struct availablesector{
    int cylinder_index;
    int track_index;
    int sector_index;
    availablesector(int cy_ind, int tr_ind, int sct_ind){
        cylinder_index = cy_ind;
        track_index = tr_ind;
        sector_index = sct_ind;
    }
    availablesector(){
        cylinder_index = -1;
        track_index = -1;
        sector_index = -1;
    }
};

inline std::ostream& operator<<(std::ostream& os, const availablesector& a){
    os << "Cylin Index " << a.cylinder_index << std::endl;
    os << "Track Index " << a.track_index << std::endl;
    os << "Sector Index " <<  a.sector_index;
    return os;
}
#endif // BLOCKDEFINITIONS_HPP
