#include <iostream>
#include "system.hpp"
#include <string>

int main(int argc, char *argv[])
{
    if(argc == 2){
        std::string filename(argv[1]);
        System system;
        system.writeFile(filename);
        system.readFile(filename);
    }
    else{
        std::cout << "no args" << std::endl;
    }
    std::string rawentry;
    do{
        std::cout << "\t**************" << std::endl;

    }while(entry != 5);
    return 0;
}
