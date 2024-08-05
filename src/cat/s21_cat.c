#include <getopt.h>

#include "delegates.h"

int main(int argc, char *argv[]) {
  char files[argc][256];
  flags flag = {0};
  if (argc < 2) {
    FILE *file = stdin;
    int c;
    while ((c = getc(file)) != EOF) {
      printf("%c", c);
    }
  }

  int file_count = 0;
  file_pars(argc, argv, files, &file_count);

  if (argv[1][0] == '-') {
    for (int i = 0; i < file_count; i++) {
      flag_pars(argc, argv, &flag);
      if (flag.error) {
        fprintf(stderr, "usage: %s [-belnstvET] [file ...]", argv[0]);
      } else {
        reader(files[i], flag);
      }
    }
  } else {
    for (int i = 1; i < argc; i++) {
      read_file(argv[i], 0, read_file_with_out_flags);
    }
  }
  return 0;
}

void flag_pars(int argc, char *argv[], flags *flag) {
  const char *sort_opt = "benstEvT";
  const struct option long_opt[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                    {"number", no_argument, NULL, 'n'},
                                    {"squeeze-blank", no_argument, NULL, 's'}};
  int res = 0;
  while ((res = getopt_long(argc, argv, sort_opt, long_opt, NULL)) != -1) {
    if (res == 'b') flag->b = 1;
    if (res == 'e') flag->e = 1;
    if (res == 'n') flag->n = 1;
    if (res == 's') flag->s = 1;
    if (res == 't') flag->t = 1;
    if (res == 'E') flag->E = 1;
    if (res == 'T') flag->T = 1;
    if (res == 'v') flag->v = 1;
    if (res == '?') flag->error = 1;
  }
}

void file_pars(int argc, char *argv[], char files[][256], int *file_count) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-' && argv[i][1] != '-') {
      strcpy(files[*file_count], argv[i]);
      *file_count += 1;
      files[*file_count][0] = '\0';
    }
  }
}

void reader(char *filepath, flags flag) {
  if (flag.v == 1) read_file(filepath, flag.v, read_file_with_v);
  if (flag.b == 1) read_file(filepath, flag.b, read_file_with_b);
  if (flag.e == 1) read_file(filepath, flag.e, read_file_with_e);
  if (flag.n == 1) read_file(filepath, flag.n, read_file_with_n);
  if (flag.s == 1) read_file(filepath, flag.s, read_file_with_s);
  if (flag.t == 1) read_file(filepath, flag.t, read_file_with_t);
  if (flag.T == 1) read_file(filepath, 0, read_file_with_t);
  if (flag.E == 1) read_file(filepath, 0, read_file_with_e);
}

void read_file(char *filepath, int flag, void (*func)(FILE *, int flag)) {
  FILE *fp = fopen(filepath, "r");
  if (fp) {
    (func)(fp, flag);
  } else {
    fprintf(stderr, "%s: No such file or directory", filepath);
  }
  fclose(fp);
}
