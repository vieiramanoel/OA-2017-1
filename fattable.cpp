#include "fattable.hpp"

FatTable::FatTable()
{
    used = std::vector<bool>(3000);
    eof = std::vector<bool>(3000);
    next = std::vector<int>(3000);
}
