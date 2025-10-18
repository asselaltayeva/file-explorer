#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void my_link(int argc, char *argv[]) {
 // Proper format
    if (argc != 4) {
	printf("Follow this format:  %s -h|-s <original_file> <link_name>\n", argv[0]);
       	return;
    }
 // Store command line
    char *option = argv[1];
    char *orig = argv[2];
    char *linkname = argv[3];
    int result;
// Create a hard link
    if (strcmp(option, "-h") == 0) {
        result = link(orig, linkname);
        if (result != 0) {
            printf("[Error code]: %s\n", strerror(errno));
            return;
        }
        printf("Hard link: %s -> %s\n", linkname, orig);
// Create a soft link
    } else if (strcmp(option, "-s") == 0) {
        result = symlink(orig, linkname);
        if (result != 0) {
            printf("[Error code]: %s\n", strerror(errno));
            return;
        }
        printf("Soft link: %s -> %s\n", linkname, orig);
    } else {
        printf("Invalid option. Use -h (hard) or -s (soft)\n");
        return;
    }
}
