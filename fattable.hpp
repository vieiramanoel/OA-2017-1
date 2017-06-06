#ifndef FATTABLE_HPP
#define FATTABLE_HPP

#include <unordered_map>
#include <vector>
#include <string>

#include "blockdefinitions.hpp"


struct sectorparams
{
    bool used {false};
    bool eof {false};
    availablesector sector;
    int next{-1};
    sectorparams(bool used, bool eof,
                 availablesector sector)
    {
        this->used = used;
        this->eof = eof;
        this->sector = sector;
    }
    sectorparams(){}
};

class FatTable
{
  public:
    FatTable();
    ~FatTable();
    void addName(availablesector sector,
                 bool iseof);
    void addNewName(std::string file_name, availablesector sector);
    int getPosition(std::string filename);
    sectorparams getSector(int position);
private:
    std::unordered_map<std::string, availablesector> table;
    std::vector<sectorparams> sector;
    sectorparams *last;

    int calculatePosition(availablesector sector);
};

#endif // FATTABLE_HPP
