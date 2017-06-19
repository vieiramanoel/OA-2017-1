#include "fattable.hpp"
#define TEMP_TRANSF_TRILHA 12
#define TEMP_LATENCIA 6
#define TEMP_MEDIO_SEEK 4

FatTable::FatTable()
{
    sector = std::vector<sectorparams>(3000);
    last = nullptr;
}

FatTable::~FatTable()
{

}

bool FatTable::addNewName(std::string filename, availablesector sector, int filesize)
{
    //method called everytime a new file is added to HDD
    int hasfileattable = getPosition(filename);
    if(hasfileattable != -1){
            std::cout << "Arquivo já existente na FAT" << std::endl;
            return false;
    }else{
        auto add_item = std::pair<std::string, availablesector>(filename, sector);
        table.insert(add_item);
        auto add_item_size = std::pair<std::string, int>(filename, filesize);
        size_table.insert(add_item_size);
        addName(sector, false);
    }
    return true;
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
    //for all new sectors on HDD add it to a space on vector
    //calculation for position given sector's coordinates is made
    //at calculatePosition method
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

std::string FatTable::printSectors(std::string filename)
{
    //runs all vector spaces that has filename sectors and return a string
    //whith all them
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
    //calculations for vector position of given sector
    //i.e
    // cylin = 0, track = 1, sector = 0, will be saved
    //at position 60 of vector
    return 300*sector.cylinder_index +
            60*sector.track_index + sector.sector_index;
}

sectorparams FatTable::getSector(int position){
    return sector[position];
}

bool FatTable::removeItem(std::string filename)
{
    int pos = getPosition(filename);
    if(pos == -1)
            return false;
    while(pos != -1){
        auto last = &sector[pos];
        sector[pos] = sectorparams();
        pos = last->next;
    }
    table.erase(filename);
    size_table.erase(filename);
    return true;
}

int FatTable::readinTime(std::string filename)
{
    //return time for read on virtual hdd
    int numsector = 1;
    int extent_time = TEMP_LATENCIA + TEMP_MEDIO_SEEK + TEMP_TRANSF_TRILHA;
    int pos = getPosition(filename);
    while(pos != -1)
    {
        numsector++;
        pos = sector[pos].next;
    }
    return (numsector * extent_time);
}

