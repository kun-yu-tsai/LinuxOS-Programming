#include <poll.h>
#include <sys/socket.h>
#include "socketLib.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buff[256];

    int serverSocket = createServerSocket();
    struct pollfd ufd;

    ufd.fd = serverSocket;
    ufd.events = POLLIN | POLLPRI;

    int ret = poll(&ufd, 1, -1);
    if (ret == -1)
    {
        printf("Error\n");
    }
    else if (ret == 0)
    {
        printf("Timeout\n");
    }
    else
    {
        if (ufd.revents & POLLIN)
        {
            // TODO: It's not gonna work. I shall do connection built here. Not receiving data.... 
            recv(ufd.fd, buff, sizeof(buff), 0);
            printf("Poll recv [%s]\n", buff);
        }
        else if (ufd.revents & POLLPRI)
        {
            recv(ufd.fd, buff, sizeof(buff), MSG_OOB); // out of band data
            printf("Poll recv out of band (exception) [%s]\n", buff);
        }
    }

    return 0;
}
