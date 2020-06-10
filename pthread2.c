#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int number = 0;
void *f1()
{
    sleep(1);
    number++;
    sleep(1);
    number++;
    sleep(1);
    number++;
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("Program start\n");

    pthread_t thread; // this is actually just a struct

    printf("Before thread create\n");

    pthread_create(&thread, NULL, f1, NULL); // after this created, the thread start to run.

    for (int i = 0; i < 5; i++)
    {
        sleep(1);
        printf("number = %d\n", number);
    }

    pthread_join(thread, NULL); // block the calling (current) thread until the designated thread finishes.
    // best practice of "join()", is called at the end of main() function.

    printf("After thread join\n");

    return 0;
}
