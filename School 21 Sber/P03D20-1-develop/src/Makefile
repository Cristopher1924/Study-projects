CC=gcc
CFLAGS=-c -Wall -Werror -Wextra

all: graph

rebuild: clean all

graph: queue.o stack.o polish_notation.o graph.o stack_double.o
	$(CC) queue.o stack.o polish_notation.o graph.o stack_double.o -o ../build/graph

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) queue.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) stack.c

stack_double.o: stack_double.c stack_double.h
	$(CC) $(CFLAGS) stack_double.c

polish_notation.o: polish_notation.c polish_notation.h stack.h queue.h
	$(CC) $(CFLAGS) polish_notation.c

graph.o: graph.c polish_notation.h stack.h queue.h
	$(CC) $(CFLAGS) graph.c 

clean:
	rm -rf *.o ../build/*
