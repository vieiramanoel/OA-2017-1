#include "system.hpp"
#include <iostream>

System::System()
{

}

System::~System()
{
    if(file.is_open())
        file.close();
}

void System::setFile(std::string filename)
{
    file = std::ifstream(filename, std::ifstream::binary);
    file.seekg(0, std::ios::beg);
}

bool System::writeFile(std::string filename)
{
    //setFile method is used to set what file we're working on
    //takes care of all file operation
    setFile(filename);

    //calculate clusters returns the number of clusters that the file
    //occup rounded up to next int
    auto clusters = calculateClusters();
    if(clusters == -1){
        return false;
    }
    //save on available sector struct next availabe sector on HDD
    auto available_sector = hdd.getNextSector();
    file.seekg(0, std::ios::beg);
    //addNewName methods returns false if file name already exists in FAT
    bool added = fat32.addNewName(filename, available_sector, filesize);
    if(!added)
        return false;
    for(int cluster = 0; cluster < clusters; cluster++){
        auto sector = available_sector;
        for(int i = 0; i < hdd.getClusterSize(); i++, sector.sector_index++){
            char *buffer = new char[512];
            file.read(buffer, 511);
            int read = file.gcount();
            buffer[read] = '\0';
            if(read < 511)
                fat32.addName(sector, true);
            else
                fat32.addName(sector, false);
                //if is last sector, save an EOF flag on FAT, else, EOF=false
            hdd.write(buffer, sector);
            delete[] buffer;
        }
        available_sector = hdd.getNextTrack(available_sector);
    }
    file.close();
    return true;
}

bool System::readFile(std::string filename)
{
    auto pos = fat32.getPosition(filename);
    if(pos == -1)
        return false;
    auto params = fat32.getSector(pos);
    std::ofstream extfile("saida.txt");
    do{
        //reinterpret_cast used for conversion between c-array and c++ string
        std::string buffer = reinterpret_cast<char*>(hdd.getbuffer(params.sector));
        //write buffer to output file
        extfile << buffer;
        pos = params.next;
        //get next position if is not EOF
        if(pos != -1)
            params = fat32.getSector(pos);
    }while(pos != -1);
    return true;
}


int System::calculateClusters()
{
    auto filesize = calculateFileSize();
    int file = (int) (filesize);
    this->filesize = file;
    if(file == -1)
        return -1;
    auto clusters = ceil( ( (float)file/(512*4) ) );
    return clusters;
}

std::streampos System::calculateFileSize()
{
    if(file){
        file.seekg(0, std::ios::beg);
        auto begin = file.tellg();
        file.seekg(0, std::ios::end);
        auto end = file.tellg();
       return end-begin;
    }
    else
        std::cout << "file error at calculate file size" << std::endl;
        std::cout << "verifique se o arquivo existe no diretório" << std::endl;

    return std::streampos(-1);
}

void System::printSizeTable()
{
    std::cout << "Nome" << "\t\tTamanho em Disco" << "\tSetores\n";
    fat32.printFileSize();
    std::cout << "\nENTER para voltar ao menu" << std::endl;
    std::cin.get();
    std::cin.get();
}

bool System::removeFatItem(std::string filename)
{
    return fat32.removeItem(filename);
}

int System::getTime(std::string filename)
{
    return fat32.readinTime(filename);
}
