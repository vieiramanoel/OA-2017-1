#ifndef VIRTUALHDD_HPP
#define VIRTUALHDD_HPP

#include "blockdefinitions.hpp"

class VirtualHdd
{
  public:
    VirtualHdd();
    ~VirtualHdd();
    int getClusterSize();
    availablesector getNextSector();
    void write(char* buffer, availablesector sector);
    availablesector getNextTrack(availablesector currsector);
    unsigned char* getbuffer(availablesector sector);
  private:

    track_array *cylinder;
    const int cylinder_amount = 10;
    int cluster_size = 4;
};

#endif // VIRTUALHDD_HPP
