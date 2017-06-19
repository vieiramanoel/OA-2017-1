#ifndef BLOCKDEFINITIONS_HPP
#define BLOCKDEFINITIONS_HPP

#define TRACKSIZE 5
#define SECTORSIZE 60
#define CLUSTEZSIZE 4
#include <iostream>
#include <ostream>
/* In this file the hdd blocks and it's aglomerations are defined
 * A block - 512 bytes
 * A sector - 4 blocks
 * A track - 60 sectors
 */

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
        //this function check if a given cluster (starting at (track, sector) is available
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
    //in order to abstract pointers to some sector or block, this struct was created to
    //save its coordinates instead of return a pointer to it
    int cylinder_index;
    int track_index;
    int sector_index;
    availablesector(int cy_ind, int tr_ind, int sct_ind){
        //you can construct struct directly with values for coordinates
        cylinder_index = cy_ind;
        track_index = tr_ind;
        sector_index = sct_ind;
    }
    availablesector(){
        //A void constructor initialize all coordinates as -1 (invalid value)
        cylinder_index = -1;
        track_index = -1;
        sector_index = -1;
    }
};

inline std::ostream& operator<<(std::ostream& os, const availablesector& a){
    //operator overload used to debug, using << operator you can print with cout
    //the coordinates that you have in some function
    //Wonderful for debbuging
    os << "Cylin Index " << a.cylinder_index << std::endl;
    os << "Track Index " << a.track_index << std::endl;
    os << "Sector Index " <<  a.sector_index;
    return os;
}
#endif // BLOCKDEFINITIONS_HPP
