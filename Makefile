.PHONY: clean

all: client server UDP_client UDP_server

client: client.c
	gcc client.c -o client

server: server.c
	gcc server.c -o server

UDP_client: UDP_client.c
	gcc UDP_client.c -o UDP_client

UDP_server: UDP_server.c
	gcc UDP_server.c -o UDP_server
clean:
	rm -rf client server UDP_client UDP_server