#include <stdlib.h>
#include <stdio.h>

#define N 20

int main(void) {
    int length;
    int i, j, count;
    
    // Get length input from user
    printf("Enter length: ");
    scanf("%d", &length);
    
    // Build array of specified length
    int array[length];

    // Get array values from user
    printf("Enter numbers: ");
    for (i=0; i<length; i++)
        scanf("%d", &array[i]);

    // Calculate the histogram
    printf("Histogram:\n");

    // Step through the all of the digits specified by N above
    for (i=0; i<=N; i++) {
        count = 0;
        // Count the values of the array that match to current digit
        for (j=0; j<length; j++)
            if (array[j] == i)
                count++;
        // Print the count for current digit
        printf("%d... %d\n", i, count);
    }

    return(0);
}
