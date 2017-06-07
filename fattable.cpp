#include "fattable.hpp"

FatTable::FatTable()
{
    sector = std::vector<sectorparams>(3000);
    last = nullptr;
}

FatTable::~FatTable()
{

}

void FatTable::addNewName(std::string file_name, availablesector sector, int filesize)
{
    auto add_item = std::pair<std::string, availablesector>(file_name, sector);
    table.insert(add_item);
    auto add_item_size = std::pair<std::string, int>(file_name, filesize);
    size_table.insert(add_item_size);
    addName(sector, false);
}

int FatTable::getPosition(std::string filename)
{
    auto pos = table.find(filename);
    if(pos == table.end())
        return -1;
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
        this->sector[position].next = -1;
        last = nullptr;
    }
    else
    {
       last = &this->sector[position];
    }
}

void FatTable::printFileSize()
{
   for(auto i : size_table){
    std::cout << i.first << "\t\t" << i.second << "\t\t" << printSectors(i.first) << std::endl;

   }
}

std::string FatTable::printSectors(std::string filename){
    int pos = getPosition(filename);
    std::ostringstream oss;
    while(pos != -1){
        oss << pos << " ";
        pos = sector[pos].next;
    }
    return std::string(oss.str());
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
