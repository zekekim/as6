#ifndef RAND64_HW_H
#define RAND64_HW_H

#include <stdbool.h>
#include <cpuid.h>
#include <immintrin.h>

/* Description of the current CPU.  */
struct cpuid { unsigned eax, ebx, ecx, edx; };

/* Return true if the CPU supports the RDRAND instruction.  */
_Bool
rdrand_supported (void);

/* Initialize the hardware rand64 implementation.  */
void
hardware_rand64_init (void);

/* Return a random value, using hardware operations.  */
unsigned long long
hardware_rand64 (void);

/* Finalize the hardware rand64 implementation.  */
void
hardware_rand64_fini (void);

#endif
