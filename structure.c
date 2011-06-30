#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int intPart;
    double fracPart;
} twoPartNum;

void decompose(double, twoPartNum*);

int main(void) {
    double number;
    twoPartNum result;

    printf("Enter number: ");
    scanf("%lf", &number);

    decompose(number, &result);
    printf("%d : %g\n", result.intPart, result.fracPart);
    return(0);
}

void decompose(double number, twoPartNum* result) {
    result->intPart = (int)number;
    result->fracPart = number - result->intPart;
}
