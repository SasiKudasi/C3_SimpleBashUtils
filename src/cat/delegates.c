#include "delegates.h"

void read_file_with_n(FILE *fp, int i) {
  i = 1;
  char prev = 'a';
  int curr;
  printf("%6d\t", i);
  while ((curr = fgetc(fp)) != EOF) {
    if (prev == '\n' && curr == '\n') {
      i++;

      printf("%6d\t", i);
    }
    if (prev == '\n' && curr != '\n') {
      i++;
      prev = curr;
      printf("%6d\t", i);
      putchar(curr);
    } else {
      prev = curr;
      putchar(curr);
    }
  }
}

void read_file_with_b(FILE *fp, int i) {
  i = 0;
  char prev = 'a';
  int curr;
  while ((curr = fgetc(fp)) != EOF) {
    if (prev == '\n' && curr == '\n') {
    }

    if (prev == '\n' && curr != '\n') {
      i++;
      prev = curr;
      printf("%6d\t", i);
      putchar(curr);
    } else {
      prev = curr;
      putchar(curr);
    }
  }
}

void read_file_with_out_flags(FILE *fp, int i) {
  while ((i = fgetc(fp)) != EOF) {
    putchar(i);
  }
}

void read_file_with_s(FILE *fp, int i) {
  int prev = '\n';
  while ((i = fgetc(fp)) != EOF) {
    if (prev == '\n' && i == '\n') {
      while ((i = fgetc(fp)) == '\n') {
      }
      putchar('\n');
      if (i == EOF) break;
    }
    putchar(i);
    prev = i;
  }
}

void read_file_with_t(FILE *fp, int flag) {
  char tab = 9;

  int curr;
  while ((curr = fgetc(fp)) != EOF) {
    if (curr == tab) {
      printf("^I");
    } else {
      if (flag == 0) {
        printf("%c", curr);
      } else {
        curr = curr_char(curr);
        printf("%c", curr);
      }
    }
  }
}

void read_file_with_v(FILE *fp, int i) {
  while ((i = fgetc(fp)) != EOF) {
    i = curr_char(i);
    putchar(i);
  }
}

char curr_char(unsigned char buff) {
  if (buff > 127 && buff < 160) printf("M-^");
  if ((buff < 32 && buff != '\n' && buff != '\t') || buff == 127) printf("^");
  if ((buff < 32 || (buff > 126 && buff < 160)) && buff != '\n' && buff != '\t')
    buff = buff > 126 ? buff - 128 + 64 : buff + 64;

  return buff;
}

void read_file_with_e(FILE *fp, int j) {
  int curr;
  while ((curr = fgetc(fp)) != EOF) {
    if (j == 1) {
      curr = curr_char(curr);
    }

    if (curr == '\n') printf("$");
    printf("%c", curr);
  }
}
