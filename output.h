#ifndef OUTPUT_H
#define OUTPUT_H

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

bool
writebytes (unsigned long long x, int nbytes, char *output);

#endif
