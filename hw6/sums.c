#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Returns sum of func from bottom to top
int sigma(int (*func)(int), int bottom, int top);

// Functions to be tested in sigma
int noop(int i);
int cubed(int i);
int halved(int i);
int firstRoot(int i);
int sined(int i);

int main(void) {
    int bottom, top, sum;

    bottom = 1; top = 100;
    sum = sigma(noop, bottom, top);
    printf("a: %d\n", sum);

    bottom = -3; top = 7;
    sum = sigma(cubed, bottom, top);
    printf("b: %d\n", sum);

    bottom = 20; top = 25;
    sum = sigma(halved, bottom, top);
    printf("c: %d\n", sum);

    bottom = 1; top = 15;
    sum = sigma(firstRoot, bottom, top);
    printf("d: %d\n", sum);

    bottom = 10; top = 15;
    sum = sigma(sined, bottom, top);
    printf("e: %d\n", sum);

    return (0);
}

int sigma(int (*func)(int), int bottom, int top) {
    int i;
    int sum = 0;
    for (i=bottom; i<=top; i++)
        sum += func(i);
    return (sum);
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
