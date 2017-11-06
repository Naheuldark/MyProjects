CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm

all: part1_1 part1_2 part2_1 part2_2

essai1: essai1.o pgm.o
	gcc $(LDFLAGS)  $^  -o $@

essai2: essai2.o pgm.o fft.o
	gcc $(LDFLAGS)  $^  -o $@

part1_1: part1_1.o pgm.o fft.o
	gcc $(LDFLAGS)  $^  -o $@	

part1_2: part1_2.o pgm.o fft.o
	gcc $(LDFLAGS)  $^  -o $@	

part2_1: part2_1.o pgm.o fft.o
	gcc $(LDFLAGS)  $^  -o $@

part2_2: part2_2.o pgm.o fft.o
	gcc $(LDFLAGS)  $^  -o $@

%.o:%.c
	gcc $(CFLAGS) $<

clean:
	rm -rf essai1 essai2 part1_1 part1_2 part2_1 part2_2 *.o
