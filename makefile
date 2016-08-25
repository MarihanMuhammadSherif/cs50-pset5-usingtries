#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

all: speller dictionary

speller: speller.c dictionary.c dictionary.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o speller speller.c dictionary.c -lcs50 -lm

dictionary: dictionary.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o dictionary dictionary.c

clean:
	rm -f *.o a.out core speller dictionary
