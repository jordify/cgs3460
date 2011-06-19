#include <stdlib.h>
#include <stdio.h>

#define N 100

int main(void) {
    int sieve[N+1];
    int i;
    int multiple;

    // Initialize the sieve
    for (i = 0; i<=N; i++)
        sieve[i] = i;

    // Perform the sieving
    sieve[1] = 0; // 1 is not prime
    for (i = 2; i<=N/2; i++) {
        if (sieve[i] != 0) { // If not 0, remove all multiples
            multiple = i*2;
            while (multiple <= N) {
                sieve[multiple] = 0;
                multiple += i;
            }
        }
    }

    // Print the primes
    for (i = 0; i<=N; i++)
        if (sieve[i] != 0)
            printf("%d\n", sieve[i]);

    return(0);
}
