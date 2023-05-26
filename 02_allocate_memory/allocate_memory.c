#include <stdio.h>
#include <stdlib.h>

void print_symbol_table(pid_t pid) {
    char maps_path[128];
    sprintf(maps_path, "/proc/%d/maps", pid);

    FILE *maps_file = fopen(maps_path, "r");
    if (maps_file == NULL) {
        perror("Failed to open /proc/<pid>/maps");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), maps_file) != NULL) {
        if (strstr(line, "/") == NULL) {
            // Skip lines that don't contain a file path (e.g., anonymous memory)
            continue;
        }

        unsigned long start, end;
        sscanf(line, "%lx-%lx", &start, &end);

        char perms[5];
        sscanf(line, "%*lx-%*lx %4s", perms);

        if (perms[0] == 'r' && perms[2] == 'x') {
            // Readable and executable memory region, consider it as a potential shared library

            char path[256];
            sscanf(line, "%*s %*s %*s %*s %*s %*s %s", path);

            printf("Shared object path: %s\n", path);
            printf("Memory address range: %lx - %lx\n", start, end);

            // You can perform further processing on the shared object, such as examining the symbol table
        }
    }

    fclose(maps_file);
}

int main() {
    pid_t pid = 31765; // Replace with the PID of the target process
    print_symbol_table(pid);
    return 0;
}

