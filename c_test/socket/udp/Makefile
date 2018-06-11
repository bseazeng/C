server-objs:=server.o
client-objs:=client.o
all:server_udp client_udp

%.o:%.c
	$(CC) -c $<
server_udp:$(server-objs)
	$(CC) -o $@ $(server-objs)
client_udp:$(client-objs)
	$(CC) -o $@ $(client-objs)
clean:
	rm *.o server_udp client_udp
