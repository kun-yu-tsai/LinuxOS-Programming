// apply pipe with thread
// also, apply close pipe write, and this will trigger termination of read.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 16
int pFds[2];

void* writePipe(){
    sleep(1);
    puts("Thread write Hello");
    write(pFds[1], "Hello", BUFFER_SIZE);
    
    sleep(1);
    puts("Thread write World");
    write(pFds[1], "World", BUFFER_SIZE);
    
    close(pFds[1]);
    puts("Thread close pipe write");
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    /*
    pipe
    create thread
    t1 write
    t2 read
    */

    pipe(pFds);

    pthread_t thread;
    pthread_create(&thread, NULL, writePipe, NULL);

    char readBuffer[BUFFER_SIZE];
    while ( read(pFds[0], readBuffer, BUFFER_SIZE) != 0)
    {
        printf("Main thread read [%s]\n",readBuffer);
    }

    puts("pipe read finished");

    return 0;
}
