#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
  while (1) {
    // List processes
    pid_t pid = 12345; /* The PID of the remote process */

    // Attach to the remote process
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
        perror("ptrace attach failed");
        return 1;
    }

    printf("Remote process paused.\n");

    char cont_p;
    printf("unpause process?");
    scanf("%c", &cont_p);
    if (cont_p == 'y') {
        printf("Continuing Process.");
        if (ptrace(PTRACE_CONT, pid, NULL, NULL) == -1) {
            perror("Failed to continue the process");
            return 1;}
    }
    else {
        printf("No?");}


  }
    return 0;
}
