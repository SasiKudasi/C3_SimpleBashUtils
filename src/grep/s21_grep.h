#ifndef S21_GREP
#define S21_GREP

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 9999
#define MAX_FILENAME_SIZE 9999

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
  int file_count;
  int patterns_count;
} flags;

void option_flag_o(char *pattern, char *line, char *filename, flags flag);
void open_file(char *filepath, char pattern[][MAX_LINE_SIZE], flags flag);
void output(char *line, char *filepath, char *patterns, flags flag, int *count,
            int line_count, int *str_count);
int reg_check(regex_t *re, char *pattern, flags flag, char *line);

void output_line(char *line, int n);
void parser(int argc, char *argv[], flags *flag, char pattern[][MAX_LINE_SIZE],
            char files[][MAX_FILENAME_SIZE]);
void option_flag_f(char *optarg, char pattern[][MAX_LINE_SIZE], flags *flag);
void file_pars(int optind, int argc, char files[][MAX_FILENAME_SIZE],
               char *argv[], flags *flag);
void copy_pattern_to_array(char patterns[][MAX_LINE_SIZE], char *argv,
                           flags *flag);
#endif