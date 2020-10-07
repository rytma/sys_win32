#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    HWND hwnd = FindWindowA(NULL, "ePSXe - Enhanced PSX emulator");
    if (hwnd == NULL) {
        printf("Cannot find window.\n");
        return -1;
    }

    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

    if (procID == NULL) {
        printf("Cannot obtain process.\n");
        return -1;
    }

    int newValue = 2500;
    WriteProcessMemory(handle, (LPVOID)0x00ABEA6C, &newValue, sizeof(newValue), 0);

    printf("Enter to exit ...");
    getchar();
    return 0;
}