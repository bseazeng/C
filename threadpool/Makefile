CFLAGS = -g
objects = thread_pool.o main.o

thread_pool: $(objects)
	$(CC) $(CFLAGS) $<

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@