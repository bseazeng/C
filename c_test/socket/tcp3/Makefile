server-objs:=server.o File.o
client-objs:=client.o
all:server_tcp client_tcp
%.o:%.c
	$(CC) -c $<
server_tcp:$(server-objs)
	$(CC) -o $@ $(server-objs) -lpthread
client_tcp:$(client-objs)
	$(CC) -o $@ $(client-objs) -lpthread
clean:
	rm *.o server_tcp client_tcp
