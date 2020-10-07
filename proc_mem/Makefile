CC := gcc

all: read write on_button

read: read_proc_mem.c
	$(CC) read_proc_mem.c -o read_proc_mem

write: write_proc_mem.c
	$(CC) write_proc_mem.c -o write_proc_mem

on_button: write_on_button_down.c
	$(CC) write_on_button_down.c -o write_on_button_down

clean:
	@del read_proc_mem.exe 2> nul
	@del write_proc_mem.exe 2> nul
	@del write_on_button_down.exe 2> nul