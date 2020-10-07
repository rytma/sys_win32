#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int
main(int argc, char *argv[]) {
    LPSYSTEM_INFO info;

    info = malloc(sizeof(SYSTEM_INFO));

    printf("Obtaining infos...\n");
    GetSystemInfo(info);
    printf("Checking objects\n");

    if (info != NULL) {
        printf( "Page Size:                  %ld\n" \
                "MinimumApplicationAddress:  %p\n" \
                "MaximumApplicationAddress:  %p\n" \
                "ActivateProcessorMask:      %ld\n" \
                "Number Of Processors:       %ld\n" \
                "Processor Type:             %ld\n" \
                "AllocationGranularity:      %ld\n" \
                "Processor Level:            %d\n" \
                "Processor Revision:         %d\n" \
                "Processor Architecture:     %d\n"
                "OemId:                      %d\n"
                "Reserved:                   %d\n",
                info->dwPageSize,
                info->lpMinimumApplicationAddress,
                info->lpMaximumApplicationAddress,
                info->dwActiveProcessorMask,
                info->dwNumberOfProcessors,
                info->dwProcessorType,
                info->dwAllocationGranularity,
                info->wProcessorLevel,
                info->wProcessorRevision,
                info->wProcessorArchitecture,
                info->dwOemId,
                info->wReserved
        );
    } else {
        printf("Error in: GetSystemInfo()");
        return 1;
    }

    return 0;
}