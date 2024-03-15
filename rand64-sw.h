#ifndef RAND64_SW_H
#define RAND64_SW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/* Software implementation.  */

/* Input stream containing random bytes.  */
extern FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (char *type);

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void);

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void);

#endif
