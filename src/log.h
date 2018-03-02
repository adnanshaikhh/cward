#pragma once

#include <stdio.h>
#include <string.h>

char error_buf[2048];
char error_str[2048];

char warning_buf[2048];
char warning_str[2048];

char debug_buf[2048];
char debug_str[2048];

#define error(MSG, ...) { \
  sprintf(error_str, "[ERROR] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  sprintf(error_buf, MSG, ##__VA_ARGS__); strcat(error_str, error_buf); \
  fprintf(stderr, "%s\n", error_str); fflush(stderr); \
  exit(EXIT_FAILURE); }

#define warning(MSG, ...) { \
  sprintf(warning_str, "[WARNING] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  sprintf(warning_buf, MSG, ##__VA_ARGS__); strcat(warning_str, warning_buf); \
  fprintf(stdout, "%s\n", warning_str); fflush(stdout); }

#define debug(MSG, ...) { \
  sprintf(debug_str, "[DEBUG] (%s:%s:%i) ", __FILE__, __func__, __LINE__); \
  sprintf(debug_buf, MSG, ##__VA_ARGS__); strcat(debug_str, debug_buf); \
  fprintf(stdout, "%s\n", debug_str); fflush(stdout); }