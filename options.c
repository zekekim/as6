#include "options.h"

void options(int argc, char **argv, long long *nbytes, char *type, char *output)
{
  bool valid = false;
  int c;
  int iflg = 0, errflg = 0;
  type = "rdrand";
  output = "stdio";
  while ((c = getopt(argc, argv, ":i:o:")) != -1)
  {
    switch (c) {
      case 'i':
        type = optarg;
        break;
      case 'o':
        output = optarg;
        break;
      case ':':       /* -f or -o without operand */
        fprintf(stderr,
          "Option -%c requires an operand\n", optopt);
        errflg++;
        break;
      case '?':
        fprintf(stderr,
          "Unrecognized option: '-%c'\n", optopt);
        errflg++;
    }
  }
  if (errflg) {
    fprintf(stderr, "usage: . . .");
    exit(2);
  }
  if (access(argv[optind], R_OK)) {
    if (optind + 1 < argc) {
      fprintf(stderr, "too many args");
    }
    char *endptr;
    errno = 0;
    *nbytes = strtoll (argv[optind], &endptr, 10);
    if (errno)
	    perror (argv[optind]);
    else
	    valid = !*endptr && 0 <= *nbytes;
  }
  if (!valid)
  {
    fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
    exit(1);
  }
}
