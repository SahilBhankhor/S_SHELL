/*

one and only purpose of this file is to take/copy code from main.cpp and rewrite it in a more optimised(readable) way

*/

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sstream>

std::vector<std::string> inBuiltCommands = {"echo", "exit", "type"};

void useEchoCommand(const std::string &userInput) // using const to prevent accidental changes (for any ranges) to the original string
{
    std::cout << userInput.substr(5) << std::endl;
}

void useTypeCommand(const std::string &checkCommand, bool &isBuiltIn)
{

    for (std::string CMD : inBuiltCommands)
    {
        if (CMD == checkCommand)
        {
            isBuiltIn = true;
            std::cout << checkCommand << " is a shell builtin" << std::endl;
        }
    }
}

void checkCommandAsPath(const std::string &checkCommand, bool &isBuiltIn)
{
    std::string PATH = getenv("PATH");
    std::stringstream ssPATH(PATH);
    char delimiter = ';';
    std::string dictionary;

    while (std::getline(ssPATH, dictionary, delimiter))
    {
        std::string currentFullPATH = dictionary + '/' + checkCommand;
        if (!access(currentFullPATH.c_str(), X_OK))
        {
            isBuiltIn = true;
            std::cout << checkCommand << " is " << currentFullPATH << std::endl;
            break;
        }
    }
}

int main()
{
    while (true)
    {
        std::string command;
        std::getline(std::cin, command);
        if (command.substr(0, 4) == "exit")
        {
            break;
        }
        else if (command.substr(0, 4) == "echo")
        {
            useEchoCommand(command);
        }
        else if (command.substr(0, 4) == "type")
        {
            bool isBuiltIn = false;
            std::string checkCommand = command.substr(5);
            useTypeCommand(checkCommand, isBuiltIn);
            if (!isBuiltIn)
            {
                checkCommandAsPath(checkCommand, isBuiltIn);
            }

            if (!isBuiltIn)
            {
                std::cout << checkCommand << ": not found" << std::endl;
            }
        }
    }

    return 0;
}
