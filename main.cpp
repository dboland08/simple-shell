#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

void printPrompt()
{
    cout << "linux dboland08|> " << flush;
}

int main()
{
    string input;

    while (true)
    {
        printPrompt();
        getline(cin, input);

        // empty input
        if (input.empty())
            continue;

        // quit
        if (input == "Q")
            break;

        // parse input into args
        char *args[100];
        char buffer[1024];
        strcpy(buffer, input.c_str());

        int i = 0;
        char *token = strtok(buffer, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // echo command
        if (strcmp(args[0], "E") == 0)
        {
            for (int j = 1; j < i; ++j)
                cout << args[j] << " ";
            cout << endl;
            continue;
        }
        // clear shell command
        if (strcmp(args[0], "W") == 0)
        {
            char *clearArgs[] = {(char *)"clear", NULL};
            int pid = fork();
            if (pid == 0)
            {
                execvp("clear", clearArgs);
                perror("execvp failed"); // prints error if clear fails
                exit(1);
            }
            else
                wait(NULL);
            continue;
        }
        // print working directory command
        if (strcmp(args[0], "L") == 0)
        {
            cout << endl;

            // run pwd
            int pid = fork();

            if (pid == 0)
            {
                char *pwdArgs[] = {(char *)"pwd", NULL};
                execvp("pwd", pwdArgs);
                perror("execvp failed");
                exit(1);
            }
            else
            {
                wait(NULL);
            }

            cout << endl;

            // run ls -l
            pid = fork();

            if (pid == 0)
            {
                char *lsArgs[] = {(char *)"ls", (char *)"-l", NULL};
                execvp("ls", lsArgs);
                perror("execvp failed");
                exit(1);
            }
            else
            {
                wait(NULL);
            }

            continue;
        }
    }
    return 0;
}