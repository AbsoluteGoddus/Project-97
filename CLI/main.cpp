#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstring>
#include <fstream>

bool win = true;

#ifdef _win32
#include <winodws.h>
win = true;
#elifdef __LINUX__
#include <cstdio>
#elifdef __APPLE__
#include <cstdio>
#endif

bool running = true;

std::string getFile(std::ifstream& file)
{
    std::string out;
    std::string tmp;
    while (std::getline(file, tmp))
    {
        out += tmp;
    }
    return out;
}

std::string message(std::string from, std::string message)
{
    auto crhTime = std::chrono::system_clock::now();
    std::time_t cmpTime = std::chrono::system_clock::to_time_t(crhTime);
    char time[100];
    std::strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", std::localtime(&cmpTime));
    std::string out;
    out = "[" + from + "] " + std::string(time) + " | " + message;
    out += "\n";
    return out;
}

std::string $message(std::string from, std::string message)
{
    auto crhTime = std::chrono::system_clock::now();
    std::time_t cmpTime = std::chrono::system_clock::to_time_t(crhTime);
    char time[100];
    std::strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", std::localtime(&cmpTime));
    std::string out;
    out = "[" + from + "]   " + std::string(time) + " | " + message;
    return out;
}

bool getOf(std::string input, int p1, int p2, std::string get)
{
    std::string copyOfIn = input.substr(p1, p2-p1);
    if (copyOfIn == get)
    {
        return true;
    }
    return false;
}

bool regCMD(std::string input)
{
    if (input == "sysok")
    {
        std::cout << message("SYSTEM", "OK");
        return true;
    }else if (input == "exit" || input == "quit")
    {
        std::cout << message("SYSTEM/CONFIRM", "Are you sure to quit? [Y/N]: ");
        std::cout << $message("USER", "> ");
        std::getline(std::cin, input);
        if (input == "Y")
        {
            running = !running;
        }

        return true;
    }else if (getOf(input, 0, 3, "get"))
    {
        if (getOf(input, 4, 6, "-d"))
        {
            std::cout << message("SYSTEM/DEBUG", "COMMAND -d FOUND");
        }

        if (getOf(input, 4, 6, "-f")) //should read get -f
        {
            std::cout << message("SYSTEM", "tsk File Name: ");
            std::getline(std::cin, input);
            std::ifstream file("../ges/" + input + ".tsk");
            if (file.is_open())
            {
                std::string out;
                out = getFile(file);
                file.close();
                std::cout << message("SYSTEM/FILE-READER/" + input + ".tsk", out);
                return true;
            }else
            {
                std::cout << message("SYSTEM/ERROR", "could not open file");
            }
        }
        return true;
    }else if (input == "cls")
    {
        if (win)
        {
            system("cls");
        }else
        {
            system("clear");
        }
        return true;
    }

    return false;
}

int main()
{
    std::string input;
    while(running)
    {
        std::cout << $message("USER", "> ");
        std::getline(std::cin, input);
        if (!regCMD(input))
        {
            std::cout << message("SYSTEM", "Command: " + input + " Not found");
        }
    }
    return 0;
}
