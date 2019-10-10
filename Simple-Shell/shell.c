#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // 1. Tokenize the command line input (split it on whitespace)
        char* command;
        char * pch;
        command = strtok (command_line, delimiters); // first string is the command
        pch = strtok (NULL, delimiters); // rest are arguments
        int i = 0;
        while (pch != NULL)
        {
          printf("Index %d ->", i);
          printf("%s\n", pch);
          arguments[i++] = pch;
          pch = strtok (NULL, delimiters);
        }
      
        // 2. Create a child process which will execute the command line input
        int cpid = fork();
        if (cpid == 0) 
        {
          printf("Executing in child process!\n");
          // The first string is the command, others are considered arguments.
          execve(command, arguments, environ);
          exit(0);
        } else if (cpid < 0)
        {
          perror("Fork error!\n");
        } else 
          
        // 3. The parent process should wait for the child to complete
        {
           int return_status;
           waitpid(cpid, &return_status, 0);
           if (return_status == 0) 
           {
             printf("Child process terminated successfully!\n");
           } else if (return_status == 1)
           {
             printf("Child process terminated with error!!!\n");
           }
        }
      
        // Hints (put these into Google):
        // man fork
        // man execve
        // man wait
        // man strtok
    }
    
    // This should never be reached.
    return -1;
}
