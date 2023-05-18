#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pid;
char cont_p;

int main() {
  while (1) {

    printf("Process Injection PID: ");

    scanf("%d", &pid);
    // List processes

    // Attach to remote process
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
        perror("ptrace attach failed");
        return 1;
    }

    printf("Remote process paused.\n");

    // Pause process
    printf("unpause process? ");
    scanf(" %c", &cont_p);
    if (cont_p == 'y') {
        printf("Continuing Process.\n");
        if (ptrace(PTRACE_CONT, pid, NULL, NULL) == -1) {
            perror("Failed to continue the process");
            return 1;}
    }
    else {
        printf("No?");}

    // Kill Process
    // Create a remote thread then open a file
    //

  }
    return 0;
}
