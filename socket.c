#include <stdio.h>
#include <sys/socket.h>


int main(int argc, char const *argv[])
{
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        puts("Socket created failed");
    }

    return 0;
}
