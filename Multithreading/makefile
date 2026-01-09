CC=gcc
CFLAGS=-I. -g -w -pthread
DEPS= wordpuzzle.c 
OBJ = wordpuzzle.c
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
wordpuzzle: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)