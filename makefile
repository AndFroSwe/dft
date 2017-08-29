# Project: dft

CC = gcc
INC = -lm
STD = -std=c11

# Compile

dft.out: dft.c
	$(CC) $(STD) -o $@ $^ $(INC)

clean:
	rm *.out *.o -f

