#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Convert permissions into a string form
void get_permissions(mode_t mode, char *perm_str) {
    strcpy(perm_str, "----------");
    if (S_ISDIR(mode)) perm_str[0] = 'd';
    else if (S_ISLNK(mode)) perm_str[0] = 'l';
    else if (S_ISCHR(mode)) perm_str[0] = 'c';
    else if (S_ISBLK(mode)) perm_str[0] = 'b';
    else if (S_ISSOCK(mode)) perm_str[0] = 's';
    else if (S_ISFIFO(mode)) perm_str[0] = 'p';

    if (mode & S_IRUSR) perm_str[1] = 'r';
    if (mode & S_IWUSR) perm_str[2] = 'w';
    if (mode & S_IXUSR) perm_str[3] = 'x';
    if (mode & S_IRGRP) perm_str[4] = 'r';
    if (mode & S_IWGRP) perm_str[5] = 'w';
    if (mode & S_IXGRP) perm_str[6] = 'x';
    if (mode & S_IROTH) perm_str[7] = 'r';
    if (mode & S_IWOTH) perm_str[8] = 'w';
    if (mode & S_IXOTH) perm_str[9] = 'x';
}

// Print file info: name, type, permissions, inode, size
void print_file_info(const char *name, const struct stat *st) {
    char perm_str[11];
    get_permissions(st->st_mode, perm_str);

    const char *ftype = "OTHER";
    if (S_ISDIR(st->st_mode)) ftype = "DIR";
    else if (S_ISREG(st->st_mode)) ftype = "FILE";
    else if (S_ISLNK(st->st_mode)) ftype = "LINK";
    else if (S_ISCHR(st->st_mode)) ftype = "CHR";
    else if (S_ISBLK(st->st_mode)) ftype = "BLK";
    else if (S_ISSOCK(st->st_mode)) ftype = "SOCK";
    else if (S_ISFIFO(st->st_mode)) ftype = "FIFO";

   // Align the table with a proper space
    printf("%-20s %-8s %-14s %-10lu %-10ld\n",
           name, ftype, perm_str, st->st_ino, (long)st->st_size);
}

void my_ls(int argc, char *argv[]) {
    int show_all = 0, show_dir_only = 0;
    const char *target = ".";

    // Command lines for ls
    if (argc > 1) {
        if (strcmp(argv[1], "-a") == 0) {
            show_all = 1;
        } else if (strcmp(argv[1], "-d") == 0) {
            show_dir_only = 1;
            if (argc > 2)
                target = argv[2];
        } else {
            fprintf(stderr, "No such option exists \"%s\". Please, try again \n", argv[1]);
            return;
        }
    } else if (argc > 2) {
        target = argv[1];
    }

    DIR *dir = opendir(target);
    if (!dir) {
        perror("opendir");
        return;
    }

    printf("\n");
    printf("%-20s %-8s %-14s %-10s %-10s\n", "Name", "Type", "Permissions", "Inode", "Size");
    printf("----------------------------------------------------------\n");

    struct dirent *entry;
    int total = 0;
    char path[4096];

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." 
        if (!show_all && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0))
            continue;

        snprintf(path, sizeof(path), "%s/%s", target, entry->d_name);

        struct stat st;
        if (stat(path, &st) == -1)
            continue;

        if (show_dir_only && !S_ISDIR(st.st_mode))
            continue;

        print_file_info(entry->d_name, &st);
        total++;
    }
    closedir(dir);
    printf("\n");
    return;
}

