#include <iostream>
#include <string>

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

      if (cmd == "echo" || cmd == "exit" || cmd == "type")
      {
        std::cout << cmd << " is a shell builtin" << std::endl;
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