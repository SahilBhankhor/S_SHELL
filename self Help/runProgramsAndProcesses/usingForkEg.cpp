#include <iostream>
#include <vector>
#include <unistd.h>
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    { // child process
        for (int i = 1; i <= 10; i++)
        {
            int sum = i * ((i + 1) / 2);
            std::cout << "sum " << "is " << sum << std::endl;
        }
    }
    else if (pid > 0)
    { // parent process
        std::vector<int> vec = {10, 20, 30, 10};
        for (int i = 0; i < vec.size(); i++)
        {
            std::cout << vec[i] << std::endl;
        }
    }

    /*
    else block is executed first , simply because first parent is created and then child is created afterwards
    */
}