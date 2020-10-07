#ifndef ERROR_H
#define ERROR_H

#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

static void print_error(const char *msg, DWORD errorMessageID) {
    if (errorMessageID == 0)
        return;
    
    LPSTR buffer;
    if (!FormatMessage(
                    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                    NULL,
                    errorMessageID,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPSTR) &buffer,
                    0,
                    NULL)) {
        fprintf(stderr, "Format message failed with %lu\n", GetLastError());
        return;
    }

    fprintf(stderr, "%s: %s", msg, buffer);
    HANDLE ProcessHeap = GetProcessHeap();
    HeapFree(ProcessHeap, 0, buffer);
}

void perr(const char *msg) {
    print_error(msg, GetLastError());
}

void perr_sock(const char *msg) {
    print_error(msg, WSAGetLastError());
}

void perr_exit(const char *msg) {
    perr(msg);
    exit(GetLastError());
}

#endif