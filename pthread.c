#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* f1(){
    sleep(1);
    printf("f1\n");
    sleep(1);
    printf("f1-2\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("Program start\n");

    pthread_t thread; // this is actually just a struct

    printf("Before thread create\n");

    pthread_create(&thread, NULL, f1, NULL); // after this created, the thread start to run.
    
    sleep(5); // even I sleep, I can still see the function running.

    pthread_join(thread, NULL); // block the calling (current) thread until the designated thread finishes.
    // best practice of "join()", is called at the end of main() function.

    printf("After thread join\n");

    return 0;
}
