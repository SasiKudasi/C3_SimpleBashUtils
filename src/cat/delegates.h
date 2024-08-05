#ifndef DELEGATES
#define DELEGATES
#define STRLENGTH 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b, e, n, s, t, v, T, E, error;
} flags;

void read_file(char *filepath, int flag, void (*func)(FILE *, int flag));
void reader(char *filepath, flags flag);
void file_pars(int argc, char *argv[], char files[][256], int *file_count);
void flag_pars(int argc, char *argv[], flags *flag);

void read_file_with_b(FILE *fp, int i);
void read_file_with_e(FILE *fp, int i);
void read_file_with_n(FILE *fp, int i);
void read_file_with_s(FILE *fp, int i);
void read_file_with_t(FILE *fp, int i);
void read_file_with_v(FILE *fp, int i);
void read_file_with_out_flags(FILE *fp, int i);
char curr_char(unsigned char buff);

#endif