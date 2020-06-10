// close pipe and read it, it will return immediately.

#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);

    close(p[1]);

    printf("%d\n", p[1]);

    char *buf[10];
    puts("read");
    int ret = read(p[0], buf, 10);

    printf("read finish with %d\n", ret);

    return 0;
}
