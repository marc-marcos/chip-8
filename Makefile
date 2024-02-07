all: Processor main

Processor: Processor.c Processor.h
	gcc -c Processor.c -o Processor.o

main: main.c
	gcc -c main.c -o main.o
	gcc main.o Processor.o -o main

clean:
	rm -f *.o
	rm main