#ifndef FATTABLE_HPP
#define FATTABLE_HPP

#include <unordered_map>
#include <vector>
#include <string>

#include "blockdefinitions.hpp"

class FatTable
{
  public:
    FatTable();
    void addName(std::string file_name, availablesector cluster);
  private:
    std::unordered_map<std::string, availablesector> table;
    std::vector<bool> used;
    std::vector<bool> eof;
    std::vector<int> next;
};

#endif // FATTABLE_HPP
