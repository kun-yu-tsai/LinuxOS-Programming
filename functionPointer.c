#include <stdio.h>

void f1(){
    printf("f1");
}

void catchFunction(void (*f)(void)){
    f();
}

int main(int argc, char const *argv[])
{
    catchFunction(f1);
    return 0;
}
