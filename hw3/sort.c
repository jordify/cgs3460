#include <stdlib.h>
#include <stdio.h>

void selection_sort(int a[], int length);

int main(void) {
    int length, i;

    // Get length
    printf("Enter number of elements: ");
    scanf("%d", &length);

    // Get array
    int a[length];
    printf("Enter array: ");
    for (i = 0; i < length; i++)
        scanf("%d", &a[i]);

    // Sort array
    selection_sort(a, length);

    // Print sorted array
    printf("Sorted array: ");
    for (i = 0; i < length; i++)
        printf("%d ", a[i]);
    printf("\n");

    return(0);
}

void selection_sort(int a[], int length) {
    int i = 0;
    int j = 0;
    int max = 0;
    int maxpos = 0;
    int b[length];
    
    // Find max element size and position
    for (i = 0 ; i < length; i++)
        if (a[i] > max) {
            max = a[i];
            maxpos = i;
        }
    
    // Make copy of rest of array without max
    for (i = 0; i < length; i++)
        if (i != maxpos) {
            b[j] = a[i];
            j++;
        }

    // Copy array back into a with max at tail
    for (i = 0; i < length-1; i++)
        a[i] = b[i];
    a[i] = max;

    // Call sort on head of list
    if (length > 2)
        selection_sort(a, length-1);
}
