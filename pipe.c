#include <stdio.h>
#include <unistd.h>

// read write in the same process.
int main(int argc, char const *argv[])
{

    int p[2];
    
    // printf("%d, %d\n", p[0], p[1]);

    if (pipe(p) < 0)
    {
        printf("Error");
        exit(-1);
    }

    // printf("%d, %d\n", p[0], p[1]);

    write(p[1], "Hello 1", 10);
    write(p[1], "Hello 2", 10);
    write(p[1], "Hello 3", 10);

    char buf[20];
    for (int i = 0; i < 3; i++)
    {
        read(p[0], buf, 30);
        printf("%s\n", buf);
    }

    return 0;
}
