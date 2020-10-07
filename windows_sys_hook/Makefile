CC = gcc

all: keyhook

keyhook: keyhook_win32.c
	$(CC) keyhook_win32.c -o keyhook.exe

clean:
	del keyhook.exe 2>nul