#include <stdio.h>
#include <stdlib.h>

struct ProcessList {
    pid_t value;
    struct ProcessList *next;
};

struct ProcessList *getProcesses() {
    struct ProcessList *process = malloc(sizeof(struct ProcessList));
    struct ProcessList *next = process;
    ProcessSerialNumber psn = { 0, kNoProcess };

    GetProcessPID(&psn, &process->next);

    while (noErr == GetNextProcess(&psn)) {
        pid_t pid;
        if (noErr == GetProcessPID(&psn, &pid)) {
            next = next->next = malloc(sizeof(struct ProcessList));
            next->value = pid;
        }
    }

    next->next = NULL;
    return process;
}

int
main(int argc, char *argv[]) {
    return 0;
}