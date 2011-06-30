#include <stdlib.h>
#include <stdio.h>

#define N 20

void histogram(int a[], int n, int h[], int n_bins);

int main(void) {
    int length;
    int i,n_bins;
    
    // Get length input from user
    printf("Enter length: ");
    scanf("%d", &length);
    
    // Build array of specified length
    int array[length];

    // Get array values from user
    printf("Enter values: ");
    for (i=0; i<length; i++)
        scanf("%d", &array[i]);

    // Get length input from user
    printf("Enter number of bins: ");
    scanf("%d", &n_bins);
    
    // Build histogram array of length n_bins
    int h[n_bins];

    // Calculate the histogram
    histogram(array, length, h, n_bins);

    // Print resulting histogram
    printf("Histogram:\n");
    for (i=0; i<n_bins; i++)
        printf("%d... %d\n", i, h[i]);

    // exit
    return(0);
}

void histogram(int a[], int n, int h[], int n_bins){
    // Get a step size N/n_bins
    int step = N/n_bins;
    int i,j,k,count;
    k = 0;
    for (i=0; i<N; i+=step) {
        count = 0;
        for (j=0; j<n; j++)
            if (a[j] >= i && a[j] < i+step)
                count++;
        h[k] = count;
        k++;
    }
}
