#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define sigma(func, bottom, top, sum)\
    do {\
        int i; \
        sum = 0; \
        for(i=bottom; i<=top; i++) \
            sum += func(i); \
    } while (0)

int noop(int i);
int cubed(int i);
int halved(int i);
int firstRoot(int i);
int sined(int i);

int main(void) {
    int bottom;
    int top;
    int sum;

    bottom = 1; top = 100;
    sigma(noop, bottom, top, sum);
    printf("a: %d\n", sum);

    bottom = -3; top = 7;
    sigma(cubed, bottom, top, sum);
    printf("b: %d\n", sum);

    bottom = 20; top = 25;
    sigma(halved, bottom, top, sum);
    printf("c: %d\n", sum);

    bottom = 1; top = 15;
    sigma(firstRoot, bottom, top, sum);
    printf("d: %d\n", sum);

    bottom = 10; top = 15;
    sigma(sined, bottom, top, sum);
    printf("e: %d\n", sum);

    return (0);
}

int noop(int i) {
    return i;
}

int cubed(int i) {
    return i*i*i;
}

int halved(int i) {
    return i/2;
}

int firstRoot(int i) {
    return (int) pow((double)i, 0.5);
}

int sined(int i) {
    return (int) sin((double)i);
}
