#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>

int main()
{
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true)
  {
    std::cout << "$ ";

    std::string command;
    std::getline(std::cin, command);

    if (command == "exit")
    {
      break;
    }

    else if (command.substr(0, 4) == "echo")
    {
      std::cout << command.substr(5) << std::endl;
    }

    else if (command.substr(0, 4) == "type")
    {
      std::string cmd = command.substr(5);
      bool isBuiltIn = false;
      if (cmd == "echo" || cmd == "exit" || cmd == "type")
      {
        isBuiltIn = true;
        std::cout << cmd << " is a shell builtin" << std::endl;
      }

      if (isBuiltIn == false)
      {
        std::string path = getenv("PATH");
        std::stringstream ssPath(path);
        std::string dictionary;
        char delimiter = ':';
        while (std::getline(ssPath, dictionary, delimiter))
        {
          std::string fullPath = dictionary + "/" + cmd;
          if (access(fullPath.c_str(), X_OK) == 0)
          {
            std::cout << cmd << " is " << fullPath << std::endl;
            break;
          }
        }
      }

      else
      {
        std::cout << cmd << ": not found" << std::endl;
      }
    }

    else
    {
      std::cout << command << ": command not found" << std::endl;
    }
  }

  return 0;
}