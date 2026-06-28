#include <iostream>
#include <cstdlib>
#include <sstream>
// #include <unistd.h> // for path.C_str() and X_OK and access() {{{ can only be used in Linux, macOS and not in Windows }}}
int main(int argc, char const *argv[])
{
    std::string path = getenv("PATH"); // gets the path access (all the paths in the system)
    std::cout << path << std::endl;    // prints all the path in single string format
    std::string args = "python";
    const char delimiter = ';'; // delimiter is always a single character not a string
    std::string dictionary;     // empty string that will hold 1 path at a time during our iteration over the path
    /*
    while(std::getline(path,dictionary,delimiter)){

    }

    here an error occurs due to getline() ,
    getline() takes the first parameter as an InputStream , but the "path" we have is a string and not a file stream
    so first we need to convert the string "path" into a file stream , and then pass that file stream to getline()

    by using  #include<sstream>  and  std::stringstream obj(path);
    i.e. ==>>  std::stringstream ssPath(path);
    */
    std::stringstream ssPath(path);
    while (std::getline(ssPath, dictionary, delimiter)) // we read each path until delimiter hits and stores that path to var "dictionary"
    {
        /*
        // for linux and Mac based systems
        std::string fullPath = dictionary + "/" + args;
        if (!access(fullPath.C_str(), X_OK))
        {
            std::cout << args << " is " << fullPath << std::endl;
        }
        */
    }
    return 0;
}
