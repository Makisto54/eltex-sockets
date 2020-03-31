#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SOCKNAME "/tmp/us_xfr"

int main()
{
    int sock;
    char buf[1024];
    int bytes_read;
    struct sockaddr_un client;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock == -1)
    {
        fprintf(stderr, "Incorrect client\n");
        exit(1);
    }
    memset(&client, 0, sizeof(struct sockaddr_un));

    client.sun_family = AF_UNIX;
    strncpy(client.sun_path, SOCKNAME, sizeof(client.sun_path) - 1);

    if(connect(sock, (struct sockaddr *)&client, sizeof(struct sockaddr_un)) == -1)
    {
        fprintf(stderr, "Incorrect client connect\n");
        exit(1);
    }

    while(1)
    {
        bytes_read = read(STDIN_FILENO, buf, 1024);
        if(bytes_read <= 0)
        {
            break;
        }
        else
        {
            write(sock, buf, bytes_read);
        }
    }
    
    close(sock);

    return 0;
}
