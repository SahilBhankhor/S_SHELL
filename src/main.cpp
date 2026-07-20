#include <iostream>
#include <string>
#include <unistd.h> // used for X_OK , c_str() , getcwd() , access() , fork()
#include <sstream>  // used to convert string to file stream
#include <vector>
#include <cerrno>
#include <climits>
#include <sys/types.h> // for pid_t , uid_t and gid_t etc.
#include <sys/wait.h>  // for wait() and waitpid()
#include <filesystem>

#ifdef _WIN32
char delimiter = ';';
#else
char delimiter = ':';
#endif

std::vector<std::string> inBuiltCommands = {"echo", "exit", "type", "pwd", "cd"};

/*

  simplifying everything I have done , until the implementation of echo exit and type commands

*/

void pwdCommand()
{
  /**
  char *pwd_buffer = getcwd(nullptr, 0);
  if (pwd_buffer != nullptr)
  {
    // std::cout << "Path:\n" << "____\n" << pwd_buffer << "\n";
    std::cout << pwd_buffer << std::endl;
    std::free(pwd_buffer);
  }
   *
   */

  std::cout << std::filesystem::current_path().string() << std::endl; // .string() is used to avoid extar double quotes that are caused by filesystem.
}

void cdCommand(const std::string &changeto)
{
  if (changeto == "" || chdir(changeto.c_str()) == 0)
    return;
  if (changeto == "~")
  {
    const char *home = getenv("HOME");
    if (home)
    {
      chdir(home);
      return;
    }
  }
  std::cout << "cd: " << changeto << ": No such file or directory" << std::endl;
  return;
}

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

bool checkCommandAsPath(const std::string &checkCommand, std::string &fullPath)
{
  std::string PATH = getenv("PATH");
  std::stringstream ssPATH(PATH);
  // char delimiter = ':';
  std::string dictionary;

  while (std::getline(ssPATH, dictionary, delimiter))
  {
    std::string currentFullPATH = dictionary + '/' + checkCommand;
    if (!access(currentFullPATH.c_str(), X_OK))
    {
      fullPath = currentFullPATH;
      return true;
    }
  }
  return false;
}

void runExternalCommand(const std::string &command)
{
  // convert sting to stream
  std::stringstream ss(command);

  // push all arguments to a vector
  std::vector<std::string> arguments;
  std::string word;
  while (ss >> word) // works like (cin >> command)
  {
    arguments.push_back(word);
  }

  // find the executable file path
  std::string execPATH;
  if (!checkCommandAsPath(arguments[0], execPATH))
  {
    std::cout << arguments[0] << ": command not found" << std::endl;
    return;
  }
  //  convert std::string ---> char*
  std::vector<char *> argvs;
  for (std::string &arg : arguments)
  {
    argvs.push_back(arg.data());
  }
  argvs.push_back(nullptr);

  // create a child process
  pid_t pid = fork();
  if (pid == 0)
  {
    // child process
    execv(execPATH.c_str(), argvs.data());

    // if execvp fails :
    perror("execv");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0)
  {
    // parent
    int status;
    waitpid(pid, &status, 0); // works like getline(cin, command)
  }
}

int main()
{
  // flushes the buffer after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // program loop
  while (true)
  {
    std::cout << "$ "; // basic symbol for all the command prompts
    std::cout.flush();
    // taking user input using getline and input stream( std::cin )
    std::string command;
    std::getline(std::cin, command);

    if (command == "exit") // to exit when user enters "exit" as input
    {
      break;
    }
    else if (command.substr(0, 3) == "pwd")
    {
      pwdCommand();
    }
    else if (command.substr(0, 2) == "cd")
    {
      cdCommand(command.substr(3));
    }
    else if (command.substr(0, 4) == "echo") // to print whatever is written right after the "echo "
    {
      useEchoCommand(command);
    }

    /*

      ----------------------------LESSER READABLE CODE FOR TYPE COMMAND--------------------------------------

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

    */
    else if (command.substr(0, 4) == "type")
    {
      bool isBuiltIn = false;
      std::string checkCommand = command.substr(5);
      useTypeCommand(checkCommand, isBuiltIn);
      if (!isBuiltIn)
      {
        std::string fullPath;
        if (checkCommandAsPath(checkCommand, fullPath))
        {
          isBuiltIn = true;
          std::cout << checkCommand << " is " << fullPath << std::endl;
        }
      }
      if (!isBuiltIn)
      {
        std::cout << checkCommand << ": not found" << std::endl;
      }
    }

    else
    {
      runExternalCommand(command);
    }
  }

  return 0;
}