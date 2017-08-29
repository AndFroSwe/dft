# Project: dft

CC = gcc
INC = -lm

# Compile

dft.out: dft.c
	$(CC)  -o $@ $^ $(INC)

clean:
	rm *.out *.o -f

