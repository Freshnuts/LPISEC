#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

struct dirent* entry;

// Check the pid directory for 'status' file.
void processInfo(const char* pid) {
    char statPath[256];

    // Call snprintf with pid value to search for status file within directories
    snprintf(statPath, sizeof(statPath), "/proc/%s/status", pid);

    // Check if status file exists with fopen()
    FILE* statFile = fopen(statPath, "r");
    if (statFile == NULL) {
        perror("fopen error");
        return;
    }

// Scan the file and look for "Name: " if found, then print.
    char processName[256];
    fscanf(statFile, "Name: %[^\n])", processName);
    fclose(statFile);

    printf("PID: %s\n", pid);
    printf("Process Name: %s\n", processName);
}

// Check all the running processes
void runningProcesses() {
    DIR* procDir = opendir("/proc");
    if (procDir == NULL) {
        perror("opendir error");
        return;
    }

    while ((entry = readdir(procDir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Check if the directory name is a numeric PID
            if (atoi(entry->d_name) != 0) {
                processInfo(entry->d_name);
                printf("\n");
            }
        }
    }

    closedir(procDir);
}

int main() {
    printf("Running Processes:\n");
    runningProcesses();

    return 0;
}

