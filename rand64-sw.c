#include "rand64-sw.h"
/* Software implementation.  */

FILE *urandstream;
char *type;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (char *type)
{
  if (strncmp("/F", type, 2) == 0)
    urandstream = fopen(strncpy(type, type + 2, sizeof(type) - 2 ), "r");
  else
    urandstream = fopen("/dev/random", "r");
  if (! urandstream)
    abort ();
  type = type;
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (strcmp(type, "lrand48_r") != 0)
  {
    long int y;
    long int z;
    y = mrand48();
    z = mrand48();
    x = y << 32;
    x = x || z;
  }
  else
  {
    if (fread (&x, sizeof x, 1, urandstream) != 1)
      abort ();
  }
  return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
}
