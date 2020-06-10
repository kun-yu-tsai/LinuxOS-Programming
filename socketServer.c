#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <unistd.h>

int main(int argc, char const *argv[])
{
    char message[256] = "Congratulation, you have reached the server successfully.";

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    puts("Server sleep");
    sleep(5);

    puts("Server listen");
    listen(server_socket, 5);

    puts("Server sleep");
    sleep(5);

    puts("Server accept");
    int clientSocketFd = accept(server_socket, NULL, NULL);
    
    puts("Server send");
    send(clientSocketFd, message, sizeof(message), 0);

    close(server_socket);

    return 0;
}
