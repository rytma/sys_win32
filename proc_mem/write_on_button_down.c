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

    float newValue = 2500;

    for (;;) {
        if (GetAsyncKeyState(VK_SPACE)) {
            WriteProcessMemory(handle, (LPVOID)0x00ABEA6C, &newValue, sizeof(newValue), 0);
            newValue++;
            printf("%d\n", newValue);
        }

        Sleep(1);
    }
    printf("Enter to exit ...");
    getchar();

    return 0;
}