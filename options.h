#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void options(int argc, char **argv, long long *nbytes, char **type, char **output);

#endif 
