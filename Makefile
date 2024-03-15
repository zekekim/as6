# Make x86-64 random byte generators.

# Copyright 2015, 2020, 2021 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# Object Files
OBJS = randall.o options.o output.o rand64-hw.o rand64-sw.o

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --gzip --transform 's,^,randall/,'
TAREXT = tgz

default: randall

randall: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

randall.o: randall.c options.h output.h rand64-hw.h rand64-sw.h
options.o: options.c options.h
output.o: output.c output.h
rand64-hw.o: rand64-hw.c rand64-hw.h
rand64-sw.o: rand64-sw.c rand64-sw.h

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission-tarball: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt # More files should be listed here, as needed.
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

repository-tarball:
	$(TAR) -czf randall-git.tgz .git

check: randall
	@echo "Checking 'randall' with various options..."
	@./randall 1024 | wc -c | grep -q '^1024$$' && \
		echo "Test passed: 'randall' outputs the correct number of bytes." || \
		echo "Test failed: 'randall' does not output the correct number of bytes."
	@./randall -i lrand48_r 1024 | wc -c | grep -q '^1024$$' && \
		echo "Test passed: 'randall -i lrand48_r' outputs the correct number of bytes." || \
		echo "Test failed: 'randall -i lrand48_r' does not output correct number of bytes."
	@./randall -o stdio 1024 | wc -c | grep -q '^1024$$' && \
		echo "Test passed: 'randall -o stdio' outputs the correct number of bytes." || \
		echo "Test failed: 'randall -o stdio' does not output the correct number of bytes."
	@./randall -o 512 1024 | wc -c | grep -q '^1024$$' && \
		echo "Test passed: 'randall -o 512' outputs the correct number of bytes." || \
		echo "Test failed: 'randall -o 512' does not output the correct number of bytes."
	@./randall -i lrand48_r -o 512 1024 | wc -c | grep -q '^1024$$' && \
		echo "Test passed: 'randall -i lrand48_r -o 512' outputs correct number bytes." || \
		echo "Test failed: 'randall -i lrand48_r -o 512' does not output the correct bytes."

.PHONY: default clean assignment submission-tarball repository-tarball check

clean:
	rm -f *.o *.$(TAREXT) randall
