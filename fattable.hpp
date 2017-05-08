#ifndef FATTABLE_HPP
#define FATTABLE_HPP

#include <unordered_map>
#include <vector>
class FatTable
{
  public:
    FatTable();
  private:
    std::unordered_map<std::string, unsigned int> table;
    std::vector<bool> used;
    std::vector<bool> eof;
    std::vector<int> next;
};

#endif // FATTABLE_HPP
