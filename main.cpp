#include <iostream>
#include <windows.h>
#include <fstream>

int main()
{
    std::cout << "Using P97 CLI v.1.0.0" << std::endl;

    while(true)
    {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "sysok")
        {
            std::cout << "ok" << std::endl;
        }else if(input == "home")
        {
            system("cls");
        }else if(input == "exit" || input == "quit")
        {
            break;
        }else if(input.substr(0, 7) == "sysload")
        {
            std::string i2 = input.substr(9, input.size());
            if (i2.substr(0, 2) == "lf")
            {
                std::fstream file(input.substr(12, input.size()), std::ios::in);
                if (file.is_open())
                {
                    std::cout << "successfully opened file" << std::endl;
                }else
                {
                    std::cerr << "error opening file" << std::endl;
                }
            }
        }else if(input == "help")
        {
            std::cout << "home | Clears The screen\nsysok | Test the system. returns ok if working and err if not\nsysload/ | flag command/ loads something from somewhere\n -lf | loads a file from an location" << std::endl;
        }
    }
}