/*
 * Homework 1: Question 4
 * Author: Jorge Gomez
 * Last Modified: Wed May 11, 2011 at 16:03
 */

#include <stdio.h>

int main(void){
    int value1, value2;
    printf("Value 1: ");
    scanf("%d", &value1);
    printf("\n");
    printf("Value 2: ");
    scanf("%d", &value2);
    printf("\n");
    printf("Switching values\n\n");
    int tmp = value1; // Temporary variable to hold old value1
    value1 = value2; // value1 <- value2
    value2 = tmp; // value2 <- tmp (old value1)
    printf("Value 1: %d\n\n", value1);
    printf("Value 2: %d\n\n", value2);
    return 0;
}
