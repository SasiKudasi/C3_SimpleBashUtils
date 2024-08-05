
#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char files[argc][MAX_FILENAME_SIZE];
  flags flag = {0};
  if (argc < 3) {
    fprintf(stderr, " Usage: %s: [OPTION]... PATTERNS [FILE]...\n", argv[0]);
    exit(1);
  }

  char pattern[argc][MAX_LINE_SIZE];
  parser(argc, argv, &flag, pattern, files);
  int count = 0;
  while (count != flag.file_count) {
    open_file(files[count], pattern, flag);
    count++;
  }
}

void parser(int argc, char *argv[], flags *flag, char pattern[][MAX_LINE_SIZE],
            char files[][MAX_FILENAME_SIZE]) {
  const char *sort_opt = "e:ivclnhsf:o";
  int res = 0;
  while ((res = getopt(argc, argv, sort_opt)) != -1) {
    switch (res) {
      case 'e':
        copy_pattern_to_array(pattern, optarg, flag);
        break;
      case 'i':
        flag->i = REG_ICASE;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        option_flag_f(optarg, pattern, flag);
        break;
      case 'o':
        flag->o = 1;
        break;
      case '?':
        exit(1);
        break;
    }
  }
  if (flag->v || flag->c || flag->l) {
    flag->o = 0;
  }

  if (flag->patterns_count < 1) {
    copy_pattern_to_array(pattern, argv[optind], flag);
    optind++;
  }
  file_pars(optind, argc, files, argv, flag);
}

void copy_pattern_to_array(char patterns[][MAX_LINE_SIZE], char *argv,
                           flags *flag) {
  strncpy(patterns[flag->patterns_count], argv + '\0', MAX_LINE_SIZE);
  //.patterns[flag->patterns_count][strlen(argv)] = '\0';
  flag->patterns_count += 1;
}

void file_pars(int optind, int argc, char files[][MAX_FILENAME_SIZE],
               char *argv[], flags *flag) {
  for (int i = optind; i < argc; i++) {
    strncpy(files[flag->file_count], argv[i], MAX_FILENAME_SIZE);
    // strcpy(files[flag->file_count], argv[i] + '\0');
    flag->file_count += 1;
  }
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (line[i] != '\n') printf("%c", line[i]);
  }
  puts("");
}

void option_flag_f(char *optarg, char pattern[][MAX_LINE_SIZE], flags *flag) {
  size_t len = 0;
  ssize_t read;
  char *line = NULL;
  FILE *fp = fopen(optarg, "r");
  if (fp) {
    while ((read = getline(&line, &len, fp)) != -1) {
      int string_legth = strlen(line);
      if (line[string_legth - 1] == '\n') line[string_legth - 1] = '\0';
      strcpy(pattern[flag->patterns_count], line);
      flag->patterns_count += 1;
    }
    fclose(fp);
  } else
    fprintf(stderr, "%s: No such file or directory\n", optarg);
}

void open_file(char *filepath, char pattern[][MAX_LINE_SIZE], flags flag) {
  size_t len = 0;
  ssize_t read;
  char *line = NULL;
  int match_count = 0;
  int count = 0;
  int line_count = 0;
  int c = 0;
  regex_t re;
  FILE *fp = fopen(filepath, "r");
  if (fp) {
    while ((read = getline(&line, &len, fp)) != -1) {
      line_count++;
      match_count = 0;

      for (int i = 0; i < flag.patterns_count; i++) {
        match_count += reg_check(&re, pattern[i], flag, line);
        if (i == flag.patterns_count - 1 && !flag.o)
          output(line, filepath, pattern[i], flag, &match_count, line_count,
                 &c);
        else if (flag.o)
          option_flag_o(pattern[i], line, filepath, flag);
        regfree(&re);
      }

      if ((count >= 0 && !flag.v) || (count < 0 && flag.v)) {
        if (flag.l) {
          printf("%s\n", filepath);
          break;
        }
      }
    }
    if (flag.c) {
      if (flag.file_count > 1 && !flag.h)
        printf("%s:%d\n", filepath, c);
      else
        printf("%d\n", c);
    }
    fclose(fp);
  } else {
    if (!flag.s) fprintf(stderr, "%s: No such file or directory\n", filepath);
  }
  if (line) free(line);
}
int reg_check(regex_t *re, char *pattern, flags flag, char *line) {
  int m = 0;
  // regex_t re;
  m = regcomp(re, pattern, flag.i);
  if (!flag.o && (m = regexec(re, line, 0, NULL, 0)) == 0)
    m = 1;
  else
    m = 0;
  return m;
}
void output(char *line, char *filepath, char *patterns, flags flag, int *count,
            int line_count, int *str_count) {
  if ((*count > 0 && !flag.v) || (flag.v && *count == 0)) {
    *str_count += 1;
    if (!flag.c && !flag.l) {
      if (!flag.h && (!flag.o && flag.file_count > 1)) printf("%s:", filepath);
      if (flag.n) printf("%d:", line_count);
      if (flag.o) {
        option_flag_o(patterns, line, filepath, flag);
      } else {
        output_line(line, strlen(line));
      }
    }
  }
}

void option_flag_o(char *pattern, char *line, char *filename, flags flag) {
  regmatch_t match;
  int offset = 0;
  regex_t re;

  int a = regcomp(&re, pattern, flag.i);
  if (a)
    exit(1);
  else {
    while (1) {
      int res = regexec(&re, line + offset, 1, &match, 0);
      if (res != 0) {
        break;
      }
      if (flag.file_count > 1) printf("%s:", filename);
      for (int i = match.rm_so; i < match.rm_eo; i++) {
        putchar(line[offset + i]);
        if (i == match.rm_eo - 1) puts("");
      }
      offset += match.rm_eo;
    }
  }
  regfree(&re);
}