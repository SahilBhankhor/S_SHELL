#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    while (true)
    {
        std::cout << "$ ";
        std::cout.flush();

        std::string line;
        std::getline(std::cin, line);

        if (line.empty())
            continue;

        // Exit command
        if (line == "exit 0")
            break;

        // Split input into arguments
        std::stringstream ss(line);
        std::vector<std::string> args;
        std::string word;

        while (ss >> word)
            args.push_back(word);

        // Convert to char* array for execvp
        std::vector<char *> argv;

        for (auto &arg : args)
            argv.push_back(arg.data());

        argv.push_back(nullptr);

        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            execvp(argv[0], argv.data());

            // Only reaches here if exec fails
            std::cerr << args[0] << ": command not found\n";
            exit(1);
        }
        else if (pid > 0)
        {
            // Parent waits
            int status;
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("fork");
        }
    }

    return 0;
}