#include "output.h"

bool writebytes(unsigned long long x, int nbytes, char* output) {
    if (strcmp(output, "stdio") == 0) {
        do {
            if (putchar(x) < 0)
                return false;
            x >>= CHAR_BIT;
            nbytes--;
        } while (nbytes > 0);
    } else {
        int blockSize = atoi(output);
        if (blockSize <= 0) {
            fprintf(stderr, "Invalid block size: %s\n", output);
            return false;
        }

        char* buffer = malloc(blockSize);
        if (!buffer) {
            perror("Failed to allocate memory");
            return false;
        }

        int index = 0;
        while (nbytes > 0) {
            buffer[index++] = x & 0xFF;
            x >>= CHAR_BIT;
            nbytes--;

            if (index == blockSize || nbytes == 0) {
                int written = write(1, buffer, index);
                if (written < 0) {
                    perror("Write error");
                    free(buffer);
                    return false;
                }
                index = 0; // reset buffer index
            }
        }

        free(buffer);
    }

    return true;
}
