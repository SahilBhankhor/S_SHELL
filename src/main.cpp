#include <iostream>
#include <string>
#include <unistd.h> // used for X_OK , c_str() and access()
#include <sstream>  // used to convert string to file stream

int main()
{
  // flushes the buffer after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // program loop
  while (true)
  {
    std::cout << "$ "; // basic symbol for all the command prompts

    // taking user input using getline and input stream( std::cin )
    std::string command;
    std::getline(std::cin, command);

    if (command == "exit") // to exit when user enters "exit" as input
    {
      break;
    }

    else if (command.substr(0, 4) == "echo") // to print whatever is written right after the "echo "
    {
      std::cout << command.substr(5) << std::endl;
    }

    else if (command.substr(0, 4) == "type") // to check whether a command is a builtin, any path / path file , or unrecognized
    {
      std::string cmd = command.substr(5);
      bool isBuiltIn = false;
      if (cmd == "echo" || cmd == "exit" || cmd == "type") // if the command is builtin
      {
        isBuiltIn = true;
        std::cout << cmd << " is a shell builtin" << std::endl;
      }

      // for path / path file , refer to /self\/Help/accessPath.cpp
      if (isBuiltIn == false) // if the command is not builtin and can likely be path / path file
      {
        std::string path = getenv("PATH");
        std::stringstream ssPath(path);
        std::string dictionary;
        char delimiter = ':';

        // we read each path until delimiter hits and stores that path to var "dictionary"
        // if any path contains that command , then it can be declared/considered as a path or path file
        while (std::getline(ssPath, dictionary, delimiter))

        {
          std::string fullPath = dictionary + "/" + cmd;
          if (access(fullPath.c_str(), X_OK) == 0)
          {
            isBuiltIn = true;
            std::cout << cmd << " is " << fullPath << std::endl;
            break;
          }
        }
      }

      if (!isBuiltIn) // if the command is unrecognized
      {
        std::cout << cmd << ": not found" << std::endl;
      }
    }

    else // " command not found " statement
    {
      std::cout << command << ": command not found" << std::endl;
    }
  }

  return 0;
}