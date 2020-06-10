#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

void handleConnection(int clientSocket);
int createServerSocket();