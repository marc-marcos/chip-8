CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: main test

main: main.o Processor.o
	$(CC) $(CFLAGS) $^ -o $@

test: test.o Processor.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c Processor.h
	$(CC) $(CFLAGS) -c $< -o $@

test.o: test.c Processor.h
	$(CC) $(CFLAGS) -c $< -o $@

Processor.o: Processor.c Processor.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o main test
