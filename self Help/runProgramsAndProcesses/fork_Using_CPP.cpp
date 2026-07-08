#include <iostream>
#include <unistd.h>
#include <sys/types.h>
/*
 * fork() creates a new process by duplicating the currently running process.
 *  Original process → Parent
    Newly created process → Child
 * Initially, the child is almost an exact copy of the parent.
 * Both processes continue execution from the next line after fork().

 */

// most of the cases parent block is executed first
// order of execution is not guranteed as both (parent and child) will run concurrently/ independently

int main()
{
    // std::cerr << "using Fedora WSL\n";
    pid_t pid = fork(); // will show error in windows , as it is a POSIX builtin , not a windows API

    /*
    everyhting that is written afterwards "pid_t pid = fork();" will be exicuted for both parent and child processes
    */
    if (pid == 0)
    {
        // std::cout << std::format("child process {} is running", pid) << std::endl; // for c++20
        std::cout << "child process " << pid << " is running" << std::endl;
    }
    else if (pid > 0)
    {
        // std::cout << std::format("parent process {} is running", pid) << std::endl; //for c++20
        std::cout << "parent process " << pid << " is running" << std::endl;
    }
    else
    {
        std::cout << "fork failed" << std::endl;
    }
}

/*
pid_t return values

Return value	        Meaning

    >0                  Parent process (value is child's PID)
     0                  Child process
    -1	                Error


*/