- <b> why getline? </b>
    + std::cin , whenever sees a space it will stop and store the input in command variable.
    + getline will store the whole input (whole line) in command variable.
    ```c++
    std::string command;
    std::getline(std::cin, command); 
    ```
- <b> using while loop for infinite commands entering </b>
    +   by using simple code(main.cpp line 11-24) , we can only execute shell only once.
    +    but users have to enter many commands in single session .
    +    so we need to run the shell in a while loop
    +    in this way the user can enter as much commands as they want.
- <b>The <u>exit</u> Builtin</b>
    + Builtin commands are handled directly by the shell without starting a new process.
    + When your shell receives the exit command, it should terminate immediately.
    + to exit when user enters "exit" as input , simply use a break statement.
    ```cpp 
    if(command == "exit"){
        break;
    }
     ```
- <b>The <u>echo</u> Builtin</b> 
    + echo command prints whatever is written right after the "echo " including all the white spaces
    + to implement "echo" we first confirm that the substring[0:4] of user input is "echo" afterWards we print all the other text(from index 5 to the end ) 
    ```cpp 
    if (command == "exit")
    {
      break;
    }
    else if (command.substr(0, 4) == "echo")
    {
      std::cout << command.substr(5) << std::endl;
    }
    
    ```
- <b>The <u>type</u> Builtin </b>
    + It checks whether a command is a builtin, an executable file, or unrecognized.
    ```cpp
    else if (command.substr(0,4) =="type"){
        if (command.substr(5) == "echo" || command.substr(5) == "exit" || command.substr(5) == "type"){
            std::cout << command.substr(5) << " is a shell command "<< std::endl;
        }else{
            std::cout << command.substr(5) << ": not found "<< std::endl;
        }
    }

    ---------------------OR------------------------------
    // to increase code readiblity , store the second substring part "command.substr(5)" into any variable "args"

    else if (command.substr(0,4) =="type"){
        std::string args = command.substr(5);
        if (args == "echo" || args == "exit" || args == "type"){
            std::cout << args << " is a shell builtin "<< std::endl;
        }
        
        
        else{
            std::cout << args << ": not found "<< std::endl;
        }
    }
    ```

- <b>Locate executable files using <u>PATH</u> </b>
    + in this case we are going to extend our "type" command
    + first , using type command , we check if the input is builtin
    + if it is not , then we check the file in the path

    + accessing path in c++
        - include cstdlib by  ``` #include <cstdlib> ```
        - to access and store the path in a variable ``` std::string path = getenv("PATH"); ```
        - the path is stored as a string , but to use it in getline() we need to convert into a file stream such as istream , stringstream etc.
        - we convert it to stringstream by ===>
            ```cpp
            #include <sstream>
            // and 
            std::stringstream ssPath(path);
            ```
        - now we are able to traverse the path to the delimiter ';'(windows) or ':' (linux)

        - <b>path.c_str() and X_ok in c++ </b>
            + c_str() is a member function of the C++ std::string class that returns a pointer to a null-terminated C-style string (const char*).
            + converts strings of C++ into C-style string by providing string address (now path.c_str() is treated as a C-style string )
            + for Linux , to use .C_str() and X_OK use ```#include <unistd.h>``` 
            + we create a var "fullpath" : 
        ```cpp
        std::string fullPath = dictionary + '/' + args ;
        if(!access(fullPath.c_str() , X_OK)){
            isBuiltIn = true;
            std::cout << cmd << " is " << fullPath << std::endl;
            break;
        }
        ```