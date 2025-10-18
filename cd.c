#include <stdio.h>    
#include <unistd.h>  
#include <limits.h> 

void  my_cd(int argc, char *argv[]) {
    // Get the directory. If not specified, stay at the current directory
    const char *target_dir = (argc == 2) ? argv[1] : ".";

    // Change the directory
    if (chdir(target_dir) != 0) {
        printf("[Error code]: No such directory: %s. Please, try again \n", target_dir);
        return;
    }

    // Store the absolute path
    char buf[PATH_MAX];

    // Show the absolute path
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("Current directory: %s\n", buf);
    } else {
        printf("[Error code]: Could not access the directory. Please, try again\n");
        return;
    }
}
