#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <stdint.h>
#include <sys/ptrace.h>
#include <sys/mman.h>


// Function to allocate, read, and write to memory space
void manipulate_remote_memory(pid_t pid) {

    unsigned long addr = 0x555555559010; // Memory address in the remote process
    char buffer[12] = "AAAABBBBCCCC"; // Data to write
    size_t size = 4096;

    struct iovec local[1];
    struct iovec remote[1];

    // Set up the local buffer for writing
    local[0].iov_base = buffer;
    local[0].iov_len = sizeof(buffer);

    // Set up the remote buffer for reading/writing
    remote[0].iov_base = (void*)addr;
    remote[0].iov_len = sizeof(buffer);



    // Perform process_vm_readv() to write the data to remote process memory
    ssize_t n = process_vm_writev(pid, local, 1, remote, 1, 0);
    if (n == -1) {
        perror("Failed to write to remote process memory");
        return;
    }

    printf("Data written to remote process memory: %s %p\n", buffer, addr);

    // Perform process_vm_readv() to read the data from remote process memory
    n = process_vm_readv(pid, remote, 1, local, 1, 0);
    if (n == -1) {
        perror("Failed to read from remote process memory");
        return;
    }

    printf("Data read from remote process memory: %s\n", buffer);
}

int main() {
    pid_t pid = 5556;
    manipulate_remote_memory(pid);
    return 0;
}
