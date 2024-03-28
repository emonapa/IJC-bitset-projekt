#-------------------------------------------------------------
#    Makefile
#    Solution to IJC-DU1, Makefile
#    Date: 14.3.2024
#    Author: Václav Matyáš, FIT
#    Compiler: gcc 11.4.0
#    Description: Makefile for build
#-------------------------------------------------------------

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
LDFLAGS = -Wall -Wextra -O2
LIBS = -lm
TARGETS = primes primes-i no-comment

.PHONY: all run clean

# Default target
all: $(TARGETS)

build: $(TARGETS)

run: $(TARGETS)
	./primes
	./primes-i

# Remove objects and executable files
clean:
	rm -f $(TARGETS) *.o

# Rules for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rules for compiling source files with inline functions
%-i.o: %.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c -o $@ $<

# Targets
primes: primes.o eratosthenes.o error.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
    
no-comment: no-comment.o error.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

