CC =gcc
CFLAGS= -I. -g -w
DEPS = bucketsort.c
OBJ = bucketsort.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
bucketsort: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
