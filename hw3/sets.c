#include <stdlib.h>
#include <stdio.h>

#define N 10

void compute_union(int set1[], int set2[], int set_union[]);
void compute_intersection(int set1[], int set2[], int set_intersection[]);
int in(int size[], int element);

int main(void) {
    int setA[N], setB[N], result_set[N];
    int element;
    int i, j;

    // Initialize empty sets
    for (i = 0; i < N; i++) {
        setA[i] = 0;
        setB[i] = 0;
    }

    // Get length input from user
    printf("Enter number of elements in set A: ");
    scanf("%d", &j);
    // Get array values from user
    printf("Enter set A: ");
    for (i = 0; i < j; i++) {
        scanf("%d", &element);
        setA[element] = 1;
    }

    // Get length input from user
    printf("Enter number of elements in set B: ");
    scanf("%d", &j);
    // Get array values from user
    printf("Enter set B: ");
    for (i = 0; i < j; i++) {
        scanf("%d", &element);
        setB[element] = 1;
    }

    printf("Union: ");
    compute_union(setA, setB, result_set);
    for (i = 0; i < N; i++)
        if (result_set[i] == 1)
            printf("%d ", i);

    printf("\nIntersection: ");
    compute_intersection(setA, setB, result_set);
    for (i = 0; i < N; i++)
        if (result_set[i] == 1)
            printf("%d ", i);

    printf("\n");
    
    return(0);
}

void compute_intersection(int set1[], int set2[], int set_union[]) {
    // Go throguh bool vector and set element to 1 if BOTH set 1
    // and set 2 have that element set to 1.
    int i = 0;
    for ( ; i < N; i++)
        if (in(set1, i) && in(set2, i))
            set_union[i] = 1;
        else
            set_union[i] = 0;
}

void compute_union(int set1[], int set2[], int set_union[]) {
    // Go throguh bool vector and set element to 1 if EITHER set 1
    // and set 2 have that element set to 1.
    int i = 0;
    for ( ; i < N; i++)
        if (in(set1, i) || in(set2, i))
            set_union[i] = 1;
        else
            set_union[i] = 0;
}

int in(int set[], int element) {
    return(set[element]);
}
