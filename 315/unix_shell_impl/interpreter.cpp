#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

/*
Splits a string input into tokens separated by delimiter
*/
std::vector<std::string> split(const std::string& input, char delimiter)
{
    std::vector<std::string> tokens;
    std::string current_token;
    // for each char, check to see if its the delimiter. If it is, create a token, else, add it to the current_token
    for (const char& c : input)
    {
        if (c == delimiter)
        {
            // If the delimiter is white space, then this might create tokens with length == 0, so we'll make sure that length > 0
            if(current_token.length() > 0){
                tokens.push_back(current_token);
                current_token.clear();
            }

        }
        else
        {
            current_token += c;
        }
    }
    tokens.push_back(current_token);
    return tokens;
}

// try to execute the command
int run_command(const std::vector<std::string>& tokens)
{
    // pid, duplicate process using fork
    pid_t pid = fork();
    // this shouldn't happen, but should be logged
    if (pid == -1)
    {
        perror("Error forking process");
        return -1;
    }
    // execute the command based on tokens
    else if (pid == 0)
    {
        // convert our vector of strings to char*
        char** args = new char*[tokens.size() + 1];
        for (int i = 0; i < tokens.size(); i++)
        {
            args[i] = const_cast<char*>(tokens[i].c_str());
        }
        // we need to add a nullptr as the last element of our char* so execvp knows when to stop
        args[tokens.size()] = nullptr;
        execvp(args[0], args);
        // raises if execvp returns -1
        perror("Error executing command");
        // cleanup
        delete[] args;
        return -1;
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
}

// runs the shell
void shell(){

    while(true){

        std::cout << "$bshell ";

        std::string in;
        // we expect our input to contain whitespaces, so we'll get the entire line
        std::getline(std::cin, in);

        /*
        The rest of these lines are written in such a way that they're quite readable.
        Essentially, the first thing that we do is separate multiple commands.
        Then, we separate each command based on the delimiter ' ', to parse the command, its flags, and its parameter
        */
        std::vector<std::string> commands_as_tokens = split(in, ';');

        for(const auto& command_as_token: commands_as_tokens)
        {

            std::vector<std::string> command_tokenized = split(command_as_token, ' ');

            run_command(command_tokenized);

        }
    }
}


int main()
{
    // start the program
    shell();

    return 0;
}
