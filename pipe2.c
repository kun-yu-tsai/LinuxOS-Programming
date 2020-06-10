#include <stdio.h>
#include <unistd.h>
#define SIZE_OF_BUFFER 16

int main(int argc, char const *argv[])
{
    int pFds[2];
    pipe(pFds); // p[0] read, p[1] write

    int pid = fork();

    if (pid == 0 /* child process */)
    {
        char *content = "Hello";
        char *content2 = " World";
        
        sleep(1);
        write(pFds[1], content, SIZE_OF_BUFFER);

        sleep(1);
        write(pFds[1], content2, SIZE_OF_BUFFER);

        sleep(5);
        write(pFds[1], content2, SIZE_OF_BUFFER);

        printf("write finished. pid = %d\n", getpid());
    }
    else
    {
        char rBuffer[SIZE_OF_BUFFER];

        puts("Start reading");

        int readSize = read(pFds[0], rBuffer, SIZE_OF_BUFFER);

        printf("content is [%s], pid = %d \n", rBuffer, getpid());

        readSize = read(pFds[0], rBuffer, SIZE_OF_BUFFER);
        printf("content is [%s], pid = %d \n", rBuffer, getpid());

        readSize = read(pFds[0], rBuffer, SIZE_OF_BUFFER);
        printf("content is [%s], pid = %d \n", rBuffer, getpid());
    }

    return 0;
}
