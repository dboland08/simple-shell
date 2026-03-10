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
        // print working directory command with ls-l
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

        // make new file command
        if (strcmp(args[0], "M") == 0)
        {
            if (i < 2) // no filename provided
            {
                cout << "Usage: M filename" << endl;
                continue;
            }

            int pid = fork();

            if (pid == 0) // child
            {
                // prepare arguments for nano
                char *nanoArgs[] = {(char *)"nano", args[1], NULL};
                execvp("nano", nanoArgs);
                perror("nano failed");
                exit(1);
            }
            else if (pid > 0) // parent
            {
                wait(NULL); // wait for nano to finish
            }
            else
            {
                perror("fork failed");
            }

            continue;
        }
        // built-in command P
        if (strcmp(args[0], "P") == 0)
        {
            if (i < 2) // no filename provided
            {
                cout << "Usage: P filename" << endl;
                continue;
            }

            int pid = fork();

            if (pid == 0) // child process
            {
                // prepare arguments for 'more'
                char *moreArgs[] = {(char *)"more", args[1], NULL};
                execvp("more", moreArgs);

                // if execvp fails
                perror("more failed");
                exit(1);
            }
            else if (pid > 0) // parent process
            {
                wait(NULL); // wait until the child process exits
            }
            else
            {
                perror("fork failed");
            }

            continue;
        }

        // copy file content to another
        if (strcmp(args[0], "C") == 0)
        {
            if (i < 3) // check if both source and destination are provided
            {
                cout << "Usage: C source_file destination_file" << endl;
                continue;
            }

            int pid = fork();

            if (pid == 0) // child process
            {
                // prepare arguments for cp
                char *cpArgs[] = {(char *)"cp", args[1], args[2], NULL};

                execvp("cp", cpArgs);

                // if execvp fails
                perror("cp failed");
                exit(1);
            }
            else if (pid > 0) // parent process
            {
                wait(NULL); // wait until child finishes copying
            }
            else
            {
                perror("fork failed");
            }

            continue;
        }

        // delete a file
        if (strcmp(args[0], "D") == 0)
        {
            if (i < 2) // check if filename is provided
            {
                cout << "Usage: D filename" << endl;
                continue;
            }

            int pid = fork();

            if (pid == 0)
            {
                char *cpArgs[] = {(char *)"rm", args[1], NULL};
                execvp("rm", cpArgs);
            }
            else if (pid >= 0)
            {
                wait(NULL);
            }
            else
            {
                perror("fork failed");
            }

            continue;
        }

        // display a help menu
        if (strcmp(args[0], "H") == 0)
        {
            cout << "\nLIST OF COMMANDS: \n\n";
            cout << "<C file1 file> |\n";
            cout << "  Copy; create file2, copy all bytes of file1 to file2 without deleting file1\n";
            cout << "<D file>\n";
            cout << "  Delete the named file\n";
            cout << "<E comment>\n";
            cout << "  Display comment on screen followed by a newline\n";
            cout << "<H>\n";
            cout << "  Help, display the user manual\n";
            cout << "<L>\n";
            cout << "  List the contents of the directory\n";
            cout << "<M file>\n";
            cout << "  Make; create the named text file by launching nano\n";
            cout << "<P file>\n";
            cout << "  Print; display the contents of the named file on screen\n";
            cout << "<Q>\n";
            cout << "  Quit the shell\n";
            cout << "<W>\n";
            cout << "  Wipe; clear the screen\n";
            cout << "<X program>\n";
            cout <<"  Execute the named program\n";
        }
    }
    return 0;
}