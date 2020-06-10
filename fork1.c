#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    int n = 10;
    printf("before fork(), current time %lu\n");
    int pid = fork();
    printf("after fork(), current time %lu\n");
    // pid 0, will return to the newly created child process.
    // wrt the parent process, it will receive the "child process pid".
    // Note, child process pid is NOT zero here!!
    if (pid == 0)
    {
        // this is the child process
        printf("Child process\n");
        printf("Child process: pid = %d \n", getpid());
        printf("Child process: parent pid = %d \n", getppid());
    }
    else
    {
        printf("Parent process\n");
        printf("Parent process: pid = %d \n", getpid());
        printf("Parent process: receive returned pid = %d \n", pid);
        sleep(5);
    }
    
    return 0;
}
