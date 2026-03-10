#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

void printPrompt()
{
    cout << "linux dboland08|> ";
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

        // built in command for E
        if (strcmp(args[0], "E") == 0)
        { 
            for (int j = 1; j < i; ++j)
                cout << args[j] << " ";
            cout << endl;
            continue;
        }
    }
    return 0;
}