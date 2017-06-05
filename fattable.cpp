#include "fattable.hpp"

FatTable::FatTable()
{
    sector = std::vector<sectorparams>(3000);
    last = nullptr;
}

FatTable::~FatTable()
{

}

void FatTable::addName(std::string file_name, availablesector cluster, bool iseof)
{
    auto add_item = std::pair<std::string, availablesector>(file_name, cluster);
    table.insert(add_item);
    int position = 10*cluster.cylinder_index +
                   5*cluster.track_index + 60*cluster.sector_index;
    sector[position] = sectorparams(true, iseof, cluster);
    if(last != nullptr)
        last->next = position;
    last = &sector[position];
}
