#ifndef ERROR_H
#define ERROR_H

// print last error
void perr(const char *msg);
// print socket specific error
void perr_sock(const char *msg);
// print last error and exit with that code
void perr_exit(const char *msg);

#endif