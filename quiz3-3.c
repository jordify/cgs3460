#include<stdio.h>
#include<stdlib.h>

#define MAXLENGTH 100

int main(void) {
    char binary[MAXLENGTH];
    int decimal;

    printf("Enter decimal number: ");
    scanf("%d", &decimal);
    
    int i = 0;

    while (decimal >= 1) {
        binary[i] = decimal % 2;
        decimal /= 2;
        i++;
    }
    i--;

    printf("Binary representation: ");
    for ( ; i >= 0; i--) 
        printf("%d", binary[i]);
    printf("\n");

    return(0);
}
