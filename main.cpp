#include <iostream>
#include "system.hpp"
#include <string>

int main()
{
    System system;
    std::string rawentry;
    int entry{0};
    std::string filename;
    do{
        std::system("clear");
        std::cout << "\t**********************" << std::endl;
        std::cout << "\t*****HD SIMULATOR*****" << std::endl;
        std::cout << "\t**********************" << std::endl;
        std::cout << "\t  Escolha uma opcao" << std::endl;
        std::cout << "1 - Adicionar arquivo ao HD" << std::endl;
        std::cout << "2 - Ler arquivo apartir da FAT" << std::endl;
        std::cout << "3 - Apagar arquivo da tabela FAT" << std::endl;
        std::cout << "4 - Mostrar Tabela FAT" << std::endl;
        std::cout << ">>> ";
        std::cin >> rawentry;
        if(rawentry.size() > sizeof(int)){
            std::cout << "Not cool, int so tem 4bytes, tente de novo" << std::endl;
        }else{
            entry = stoi(rawentry);
        }
        std::system("clear");
        bool success;
        switch (entry) {
        case 1:
            std::cout << "Digite o nome do arquivo texto:\n>>> ";
            std::cin >> filename;
            success = system.writeFile(filename);
            if(!success)
                std::cout << "Tente um arquivo existente no diretório\n "
                             "ENTER para continar" << std::endl;
            else
                std::cout << "Feito! ENTER para continuar" << std::endl;
            std::cin.get();
            std::cin.get();
            break;
        case 2:
            std::cout << "Digite o nome do arquivo texto:\n>>> ";
            std::cin >> filename;
            success = system.readFile(filename);
            if(!success)
                std::cout << "Tente um arquivo existente na FAT\n "
                             "ENTER para continar" << std::endl;
            else
            	std::cout << "Tempo de leitura: " << readingTime(filename) << 'ms\n' << std::endl
                std::cout << "Feito! ENTER para continuar" << std::endl;
            std::cin.get();
            std::cin.get();
            break;
        case 3:
            std::cout << "Digite o nome do arquivo a ser removido\n>>>";
            std::cin >> filename;
            success = system.removeFatItem(filename);
            if(!success)
                std::cout << "Tente um arquivo existente na FAT\n "
                             "ENTER para continar" << std::endl;
            else
                std::cout << "Feito! ENTER para continuar" << std::endl;
            std::cin.get();
            std::cin.get();
            break;
        case 4:
            system.printSizeTable();
            break;
        case 5:
            break;
        case 0:
        default:
            entry = 0;
            std::cout << "Entrada inválida, tente novamente\n"
                         "ENTER para continuar" << std::endl;
            std::cin.get();
            std::cin.get();
            std::system("clear");
            break;
        }
    }while(entry != 5);
    return 0;
}
