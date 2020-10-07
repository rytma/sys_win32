#include "sock.h"

unsigned int send_file(const char *server, unsigned int port, const HANDLE hFile) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (!is_socket_valid(sock)) {
        perr_sock("socket creation error");
        socket_cleanup();
        exit(1);
    }

    PLARGE_INTEGER fSize;
    if (GetFileSizeEx(hFile, fSize)) {
        CloseHandle(hFile);
        perr_exit("Error: GetFileSizeEx");
    }

    do {
        int ret;
        if ((ret = send(sock, buffer, count, 0)) < 0) {
            perr("socket send error")
        }
    }
}