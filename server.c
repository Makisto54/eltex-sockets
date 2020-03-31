#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define SOCKNAME "/tmp/us_xfr"

int main()
{
    int sock, new_sock;
    struct sockaddr_un server;
    char buf[1024];
    int bytes_read;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock == -1)
    {
        fprintf(stderr, "Incorrect server\n");
        exit(1);
    }
    if(remove(SOCKNAME) == -1 && errno != ENOENT)
    {
        fprintf(stderr, "Incorrect server\n");
        exit(1);
    }

    memset(&server, 0, sizeof(struct sockaddr_un));

    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, SOCKNAME, sizeof(server.sun_path) - 1);

    if(bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) == -1)
    {
        fprintf(stderr, "Incorrect server bind\n");
        exit(1);
    }

    if(listen(sock, 1) == -1)
    {
        fprintf(stderr, "Incorrect server listen\n");
        exit(1);
    }    

    new_sock = accept(sock, NULL, NULL);
    if(new_sock == -1)
    {
        fprintf(stderr, "Incorrect server accept\n");
        exit(1);
    }

    printf("Connected!\n");
    while(1)
    {
        bytes_read = read(new_sock, buf, 1024);
        if(bytes_read <= 0) 
        {
            break;
        }
        else
        {
            write(STDOUT_FILENO, buf, bytes_read);
        }
    }
    
    close(new_sock);
    close(sock);

    return 0;
}
