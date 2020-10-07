#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Psapi.h>
#include <tchar.h>

void
PrintProcessNameAndID( DWORD processID ) {
    TCHAR szProcessName[MAX_PATH] = TEXT("<uknown>");

    // Get a handle to process
    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        processID
    );

    if (hProcess != NULL) {
        HMODULE hMod;
        unsigned long cbNeeded;

        if ( EnumProcessModules(
                    hProcess,
                    &hMod,
                    sizeof(hMod),
                    &cbNeeded
        ) ) {
            GetModuleBaseName(
                hProcess,
                hMod,
                szProcessName,
                sizeof(szProcessName) / sizeof(TCHAR)
            );
        }
    }

    printf("%s (PID %u)\n", szProcessName, processID);

    CloseHandle(hProcess);
}

int
main(int argc, char *argv[]) {
    unsigned long aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) ) return 1;

    cProcesses = cbNeeded / sizeof(DWORD);

    for (i = 0; i < cProcesses; i++) {
        if ( aProcesses[i] != 0) {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }

    return 0;
}