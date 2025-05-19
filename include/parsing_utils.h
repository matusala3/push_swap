#ifndef PARSING_UTILS_H
#define PARSING_UTILS_H

#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

bool safe_atoi(const char *str, int *out);

#endif