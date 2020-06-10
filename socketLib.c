#include "socketLib.h"

void handleConnection(int clientSocket)
{
    char message[] = "Hello from server";
    send(clientSocket, message, sizeof(message), 0);

    char buff[256];
    recv(clientSocket, buff, sizeof(buff), 0);
    printf("Recv from client [%s]", buff);

    close(clientSocket);
}

int createServerSocket()
{
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(fd, 5);
    return fd;
}