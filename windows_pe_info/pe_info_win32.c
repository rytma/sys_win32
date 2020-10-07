// https://ntcore.com/files/pe.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char **argv) {
	HANDLE hFile, hMapObj, hBaseAddress;
	IMAGE_DOS_HEADER *ImageDosHeader;

	printf("\nOpening file...\n");

	hFile = CreateFile(
		"prova.exe",
		GENERIC_READ,
		FILE_SHARE_READ,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		printf("Cannot open the file\n");
		return -1;
	}

	hMapObj = CreateFileMapping(
		hFile,
		NULL,
		PAGE_READONLY,
		0,
		0,
		0
	);

	if (!hMapObj) {
		CloseHandle(hFile);
		printf("Cannot create file mapping\n");
		return -1;
	}

	if (!hBaseAddress == MapViewOfFile(
							hMapObj,
							FILE_MAP_READ,
							0,
							0,
							0)) {
		CloseHandle(hMapObj);
		CloseHandle(hFile);
		printf("Cannot create map view of file\n");
		return -1;
	}

	printf("File mapped in memory\n");

	// iniziamo dal hBaseAddress la lettura dell'header
	ImageDosHeader = (IMAGE_DOS_HEADER *) hBaseAddress;

	// controlliamo il dos header (e_magic it's a magic number)
	if (ImageDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		printf("Invalid DOS Header\n");
		goto Close_Handle;
	}

	// e_lfanew it's a file address f new exe header
	printf("Valid DOS Header\n");
	printf("File offset: %X\n", ImageDosHeader->e_lfanew);


Close_Handle:
	UnMapViewOfFile(hBaseAddress);
	CloseHandle(hMapObj);
	CloseHandle(hFile);

	printf("File closed\n");
	return 0;
}