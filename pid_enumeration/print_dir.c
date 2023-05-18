#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Failed to open directory");
        return 1;
    }
    

    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(*entry->d_name)) {
          printf("%s\n", entry->d_name);}}

    closedir(dir);

    return 0;
}

