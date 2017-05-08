#ifndef BLOCKDEFINITIONS_HPP
#define BLOCKDEFINITIONS_HPP

#include <iostream>

struct block{
    unsigned char bytes_s[512];
    block(){
        for(auto i = 0; i < 512; i++)
            bytes_s[i] = (unsigned char) 0;
        for(int i = 0; i < 512; i++){
            if(i == 511){
                std::cout << i << " " << std::endl;
            }
        }
    }
};

struct sector_array{
    block sector[60];
};

struct track_array{
    sector_array track[5];
};

struct fatent_s{
    unsigned int used;
    unsigned int eof;
    unsigned int next;
};

#endif // BLOCKDEFINITIONS_HPP
