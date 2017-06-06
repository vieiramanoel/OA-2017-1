#include "fattable.hpp"

FatTable::FatTable()
{
    sector = std::vector<sectorparams>(3000);
    last = nullptr;
}

FatTable::~FatTable()
{

}

void FatTable::addNewName(std::string file_name, availablesector sector)
{
    auto add_item = std::pair<std::string, availablesector>(file_name, sector);
    table.insert(add_item);
    addName(sector, false);
}

int FatTable::getPosition(std::string filename)
{
    auto pos = table.find(filename);
    return calculatePosition(pos->second);
}

void FatTable::addName(availablesector sector, bool iseof)
{
    int position = calculatePosition(sector);
    this->sector[position] = sectorparams(true, iseof, sector);
    if(last != nullptr)
        last->next = position;
    if(iseof)
    {
        std::cout << sector << std::endl;
        this->sector[position].next = -1;
        last = nullptr;
    }
    else
    {
       last = &this->sector[position];
    }
}

int FatTable::calculatePosition(availablesector sector)
{
    //some questions about position calculation, check later
    return 300*sector.cylinder_index +
            60*sector.track_index + sector.sector_index;
}

sectorparams FatTable::getSector(int position){
    return sector[position];
}
