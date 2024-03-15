#include "options.h"

void options(int argc, char **argv, long long *nbytes, char **type, char **output)
{
  bool valid = false;
  int c;
  *type = "rdrand"; // Default value
  *output = "stdio"; // Default value

  while ((c = getopt(argc, argv, ":i:o:")) != -1)
  {
    switch (c) {
      case 'i':
        *type = optarg;
        break;
      case 'o':
        *output = optarg;
        break;
      case ':': // -i or -o without operand
        fprintf(stderr, "Option -%c requires an operand\n", optopt);
        exit(2);
      case '?':
        fprintf(stderr, "Unrecognized option: '-%c'\n", optopt);
        exit(2);
    }
  }

  if (optind < argc) {
    char *endptr;
    errno = 0;
    *nbytes = strtoll(argv[optind], &endptr, 10);
    if (errno) {
      perror("Error parsing NBYTES");
      exit(1);
    }
    valid = (*endptr == '\0' && *nbytes >= 0);
  }

  if (!valid) {
    fprintf(stderr, "%s: usage: %s [-i type] [-o output] NBYTES\n", argv[0], argv[0]);
    exit(1);
  }
}

