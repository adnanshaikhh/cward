#pragma once

#include <stdio.h>

#define TODO(msg) todo_abort(__func__, msg)

void todo_abort(const char *func, const char *msg)
{
  fprintf(stderr, "TODO %s: %s\n", func, msg);
  abort();
}
