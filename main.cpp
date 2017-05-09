#include <iostream>
#include "system.hpp"
#include <string>

int main(int argc, char *argv[])
{
    if(argc == 2){
        std::string filename(argv[1]);
        System system(filename);
        system.writeFile();
    }
    else{
        std::cout << "no args" << std::endl;
    }
    return 0;
}
