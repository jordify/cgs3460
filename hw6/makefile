CC = gcc
JPEGOBJ = jpeg32.o

all: sums histogram

sums: sums.c
	$(CC) -Wall -lm -o sums sums.c

histogram: histogram.c histogram.h
	$(CC) -Wall -ljpeg -o histogram $(JPEGOBJ) histogram.c

debug: histogram.c histogram.h
	$(CC) -Wall -ljpeg -ggdb -DDEBUG -o histogram $(JPEGOBJ) histogram.c

clean:
	\rm -f sums histogram *.tar

tar:
	mkdir homework6
	cp sums.c homework6/
	cp histogram.{c,h} homework6/
	cp jpeg{32,64}.o homework6/
	cp jpeg.h homework6/
	cp makefile homework6/
	cp README homework6/
	tar cvf homework6.tar homework6/*
	rm homework6/*
	rmdir homework6
