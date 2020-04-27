#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() 
{
	int i = 0;
    int sock;
    int size;
    char buf[1024];
    char buf2[1024];
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
    {
    	fprintf(stderr, "Incorrect client socket\n");
        exit(1);
	}

    server.sin_family = AF_INET;
    server.sin_port = htons(0xAABB);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    size = sizeof(server);
    printf("Connected!\n");
    while(i < 10)
	{
        fgets(buf, 1024, stdin);
        if(sendto(sock, buf, 1024, 0, (struct sockaddr *) &server, size) < 0)
        {
        	fprintf(stderr, "Incorrect client send\n");
            exit(1);
		}
        if(recvfrom(sock, buf2, 1024, 0, (struct sockaddr *) &server, &size) == -1)
        {
        	fprintf(stderr, "Incorrect client recv\n");
            exit(1);
		}
		printf("Server sends - %s\nMessages - %d\n", buf2, 9 - i++);
    }
    
    return 0;
}
