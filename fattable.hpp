#ifndef FATTABLE_HPP
#define FATTABLE_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include "blockdefinitions.hpp"

/* Definition of FatTable class which map all sectors to
 * a table using FAT theory
 * To abstract tables and multdimensional matrices, unordered_map
 * was used (C++14), this data struct also map its keys using hashing
 * making search in it extremely fast
 */

struct sectorparams
{
    bool used {false};
    bool eof {false};
    availablesector sector; //hold sector coordinates
    int next{-1};
    sectorparams(bool used, bool eof,
                 availablesector sector)
    {
        //constructor using parameters
        this->used = used;
        this->eof = eof;
        this->sector = sector;
    }
    sectorparams(){
        //void constructor
        used = false;
        eof = false;
        availablesector sector;
        next = -1;
    }
};

class FatTable
{
  public:
    FatTable();
    ~FatTable();
    void addName(availablesector sector,
                 bool iseof);
    bool addNewName(std::string filename, availablesector sector, int filesize);
    int getPosition(std::string filename);
    sectorparams getSector(int position);
    void printFileSize();
    bool removeItem(std::string filename);
	int readinTime(std::string filename);
private:
    std::unordered_map<std::string, availablesector> table;
    std::unordered_map<std::string, int> size_table;
    std::vector<sectorparams> sector;
    sectorparams *last;

    int calculatePosition(availablesector sector);
    std::string printSectors(std::string filename);
};

#endif // FATTABLE_HPP
