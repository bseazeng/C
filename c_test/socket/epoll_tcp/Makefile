server-objs:=epoll_server.o
client-objs:=epoll_client.o
all:server_tcp client_tcp
%.o:%.c
	$(CC) -c $<
server_tcp:$(server-objs)
	$(CC) -o $@ $(server-objs)
client_tcp:$(client-objs)
	$(CC) -o $@ $(client-objs)
clean:
	rm *.o
