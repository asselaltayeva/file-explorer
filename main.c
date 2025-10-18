#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void my_ls(int argc, char *argv[]);
void my_cd(int argc, char *argv[]);
void my_link(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    char cwd[PATH_MAX];
    char input[256];
    char *args[16];
    int argcount;

    if (argc == 2 && chdir(argv[1]) != 0) {
        printf("[Error code 1]: no such directory\n");
    }
    printf("\n\n*************   assel_explorer START   *************\n\n");

    while (1) {
        if (!getcwd(cwd, sizeof(cwd))) strcpy(cwd, ".");
        printf("*assel_explorer* %s > ", cwd);

        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0'; // Strip newline

        // Split input into seperate forms
        argcount = 0;
        char *token = strtok(input, " ");
        while (token && argcount < 16) {
            args[argcount++] = token;
            token = strtok(NULL, " ");
        }
        if (argcount == 0) continue;

        // Command execution
        if (strcmp(args[0], "quit") == 0) {
            break;
        }
        else if (strcmp(args[0], "ls") == 0) {
            my_ls(argcount, args);
        }
        else if (strcmp(args[0], "cd") == 0) {
            my_cd(argcount, args);
        }
        else if (strcmp(args[0], "link") == 0) {
            my_link(argcount, args);
        }
        else {
            printf("[Error code 1]: no such option like '%s'.\n", args[0]);
        }
    }
    printf("\n*************   assel_explorer EXIT   *************\n");
    return 0;
}


