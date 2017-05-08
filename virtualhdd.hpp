#ifndef VIRTUALHDD_HPP
#define VIRTUALHDD_HPP

#include "blockdefinitions.hpp"

class VirtualHdd
{
  public:
    VirtualHdd();
    ~VirtualHdd();
    int getSectorSize();
    int getNextSector();
  private:
    track_array *cylinder;
    int cylinderamount = 10;
    int sector_size = 4;
};

#endif // VIRTUALHDD_HPP
