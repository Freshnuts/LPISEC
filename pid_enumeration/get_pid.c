#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <dirent.h>

int main() {
    pid_t pid = 0;
    int pidInput;

    // Get local PIDs
    pid = syscall(__NR_getpid);
    printf("Local Process ID: %d\n", pid);

    // Get remote PIDs
    printf("Input Remote Process ID: ");
    scanf("%d", &pidInput);

    if (kill(pidInput, 0) == 0) {
        printf("Remote Process ID: %d\n", pidInput);} 
    else {
        perror("Failed to obtain process ID");}

    // List of Remote PIDs
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == NULL) {
      perror("Failed to open directory");
      return 1;}

    while ((entry = readdir(dir)) != NULL) {
      if (isdigit(*entry->d_name)) {
        // read directory
        // look for file 'status'
        // read file status for 'name: process name'
        printf("%s\n", entry->d_name);}}

    closedir(dir);

    return 0;
}

