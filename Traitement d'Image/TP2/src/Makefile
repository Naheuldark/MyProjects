CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm

part1_1: part1_1.o pgm.o fft.o filtres.o
	gcc $(LDFLAGS)  $^  -o $@

%.o:%.c
	gcc $(CFLAGS) $<

clean:
	rm -rf essai1 essai2 *.o