#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    /*
    read html file into a character array (as the body)
    build header content
    combine header and body
    create socket and listen
    accept and send "header and body".
    */

    char content[2048] = "HTTP/1.1 200 OK\r\n\n<html><body>Hi</body></html>";

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in socketInfo;
    socketInfo.sin_family = AF_INET;
    socketInfo.sin_port = htons(9002);
    socketInfo.sin_addr.s_addr = INADDR_ANY;

    bind(socketServer, (struct sockaddr *)&socketInfo, sizeof(socketInfo));

    listen(socketServer, 5);

    int clientSocket;
    while (1)
    {
        clientSocket = accept(socketServer, NULL, NULL);
        send(clientSocket, content, sizeof(content), 0);
    }

    close(socketServer);

    return 0;
}
