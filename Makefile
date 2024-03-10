CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: main

main: main.o Processor.o Utils.o
	$(CC) $(CFLAGS) $^ -o $@

test: test.o Processor.o Utils.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

main.o: main.c Processor.h
	$(CC) $(CFLAGS) -c $< -o $@

test.o: test.c Processor.h
	$(CC) $(CFLAGS) -c $< -o $@

Processor.o: Processor.c Processor.h
	$(CC) $(CFLAGS) -c $< -o $@

Utils.o: Utils.c Utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o main test
