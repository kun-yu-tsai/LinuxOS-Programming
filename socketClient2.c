#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

// #include <string.h>

#include <unistd.h>

/*

struct sockaddr_in {
    short            sin_family;   // AF_INET,因為這是IPv4;
    unsigned short   sin_port;     // 儲存port No
    struct in_addr   sin_addr;     // 參見struct in_addr
    char             sin_zero[8];  // Not used, must be zero 
};

struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
	__uint8_t       sa_len;          total length 
	sa_family_t     sa_family;       [XSI] address family 
	char            sa_data[14];     [XSI] addr value (actually larger) 
};

*/

int main(int argc, char const *argv[])
{
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        puts("Socket created failed");
    }

    struct sockaddr_in info;

    // bzero(&info, sizeof(info));

    info.sin_family = AF_INET; // IPV4

    // inet_addr convert string format IP address to 32 bits integer address.
    // (which is the real one used by the computers among the network.)
    info.sin_addr.s_addr = INADDR_ANY;

    // host to network short (it has siblings of htol to deal with long value)
    // network uses Big endian when it comes to bits form.
    info.sin_port = htons(9002);

    // server socket has to set up "listen" flag before this statement.
    puts("Client call connect");
    int ret = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
    if (ret == -1)
    {
        printf("Connect error\n");
        return -1;
    }

    char response[256];
    
    puts("Client call recv");
    recv(sockfd, response, sizeof(response), 0);
    printf("Recv response [%s]\n", response);
    
    puts("Client call send");
    char clientMsg[] = "A message from client";
    send(sockfd, clientMsg, sizeof(clientMsg), 0);

    close(sockfd);

    return 0;
}
