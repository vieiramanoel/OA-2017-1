#include <iostream>
#include "system.hpp"
#include <string>

int main(int argc, char *argv[])
{
    std::string filename("teste.txt");
    System system(filename);
    system.writeFile();
    return 0;
}
