#include "fattable.hpp"

FatTable::FatTable()
{
    used = std::vector<bool>(3000);
    eof = std::vector<bool>(3000);
    next = std::vector<int>(3000);
}

void FatTable::addName(std::string file_name, availablesector cluster)
{
    auto add_item = std::pair<std::string, availablesector>(file_name, cluster);
    table.insert(add_item);
}
