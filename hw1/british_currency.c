/*
 * Homework 1: Question 3
 * Author: Jorge Gomez
 * Last Modified: Wed May 11, 2011 at 15:32
 */

#include <stdio.h>

int main(void){
    int pounds, shillings, pennies;
    printf("**************************************\n");
    printf("\n");
    printf("* British Monetary system conversion *\n");
    printf("\n");
    printf("**************************************\n");
    printf("\n");
    printf("* Enter old currency: ");
    scanf("%d.%d.%d", &pounds, &shillings, &pennies);
    printf("\n");
    // pence = 100*(amount of pennies / total pennies per pound (20*12))
    int pence = (12*shillings + pennies)/2.4;
    printf("* New currency equivalent: %d.%d\n", pounds, pence);
    printf("\n");
    return 0;
}
