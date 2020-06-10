#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

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

void handleConnection(int clientSocket)
{
    char message[] = "Hello from server";
    send(clientSocket, message, sizeof(message), 0);

    char buff[256];
    recv(clientSocket, buff, sizeof(buff), 0);
    printf("Recv from client [%s]", buff);

    close(clientSocket);
}

int main(int argc, char const *argv[])
{
    fd_set socketSet;
    fd_set selectedSocketSet;
    int serverSocket = createServerSocket();
    printf("server socket = %d\n", serverSocket);

    FD_ZERO(&socketSet);
    FD_SET(serverSocket, &socketSet);

    while (1)
    {
        selectedSocketSet = socketSet; // assign (copy) values;
        
        printf("start to select [%s], [%s]\n", __TIME__, __TIMESTAMP__);
        if (select(FD_SETSIZE, &selectedSocketSet, NULL, NULL, NULL) < 0)
        {
            printf("select error");
            return -1;
        }

        printf("end select [%s], [%s]\n", __TIME__, __TIMESTAMP__);

        for (int fd = 0; fd < FD_SETSIZE; fd++)
        {
            if (FD_ISSET(fd, &selectedSocketSet))
            {
                if (fd == serverSocket)
                {
                    // create client socket, and set client socket into sockets
                    int clientSocket = accept(serverSocket, NULL, NULL);
                    FD_SET(clientSocket, &socketSet);
                    printf("Create client socket\n");
                }
                else
                {
                    handleConnection(fd);
                    FD_CLR(fd, &socketSet);
                }
            }
        }
    }

    return 0;
}
