#include <stdio.h>

float absDiff(float a, float b) {
    float diff;
    diff = (float)a-b;
    if (diff<0) return diff*-1;
    else return diff;
}

int main() {
    int a, b, c;
    int i;
    int decimalPoints;
    float lastApprox, thisApprox;
    float precision = 1.0;

    printf("Decimal places for golden ratio: ");
    scanf("%d", &decimalPoints);

    for(i=0; i<decimalPoints; i++) {
        precision = precision/10;
    }

    a = 1;
    b = 1;
    c = a+b;
    lastApprox = 1.0;
    thisApprox = (float)c/b;

    while (absDiff(thisApprox, lastApprox)>precision) {
        a = b;
        b = c;
        c = a+b;
        lastApprox = thisApprox;
        thisApprox = (float)c/b;
    }

    printf("%.10f\n", thisApprox);
    return 0;
}
