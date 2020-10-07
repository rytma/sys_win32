#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Lmcons.h>

int main(int argc, char **argv) {
    char user[UNLEN+1];
    DWORD user_l = UNLEN+1;
    GetUserNameA(user, &user_l);

    char *startup_folder;
    if ((startup_folder = malloc((UNLEN+77+user_l) * sizeof(char))) == NULL) {
        fprintf(stderr, "Error: not memory space\n");
        return 1;
    }

    sprintf(startup_folder, "C:\\Users\\%s\\AppData\\Roaming\\"
            "Microsoft\\Windows\\Start Menu\\Programs\\Startup\\%s",
            user, argv[1]);
    
    if (!MoveFile(argv[1], startup_folder)) {
        fprintf(stderr, "Error: file %s not moved", argv[1]);
        return 1;
    }
    printf("Moved File\n");

    return 0;
}