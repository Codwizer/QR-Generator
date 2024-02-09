CC=g++

all: main

main: main.cpp 
	$(CC) -ggdb -o main main.cpp -lqrencode


.PHONY clean:
	rm main
