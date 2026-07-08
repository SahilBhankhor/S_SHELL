// available in header <unistd.h>

/*
exec() POSIX does not create any new processes
instead
it replaces the current process in the memory with a new process
process id remains the same


if a seperate process is to be created , then we first use fork() and then exec()
this way we are firstly creating a copy of the current process and then replacing its memory with a new process
*/
#include <iostream>
#include <unistd.h>
int main(int argc, char const *argv[])
{

    return 0;
}
/*
there is an entire family of these exec functions

commonly used are :
execl()
execv()
execvp()
execve()
execle()
execvpe()

*/

/*
exec() member used most commonly in building a shell is  "execvp()"

*/