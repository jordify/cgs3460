#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFTAMT        20
#define BUF_SIZE        512

int main() {
    char a;
    int i,j;

    char inBuf[BUF_SIZE];
    char* input = malloc(sizeof(char)*BUF_SIZE);

    size_t inputSize = 1; // Just NUL at first

    input[0] = '\0';

    // Get plain text from stdin until EOF
    while(fgets(inBuf, BUF_SIZE, stdin)) {
        inputSize += strlen(inBuf);
        input = realloc(input, inputSize);
        strcat(input, inBuf);
    }

    char* output = malloc((int)(1.2*sizeof(char)*strlen(input)));

    j = 0;
    int written = 0;
    for (i = 0; i < strlen(input); i++) {
        if (written==5) {
            // Write a space every 5 cipher characters
            written = 0;
            output[j] = ' ';
            j++;
        }

        a = input[i];
        if ((int)a < 123 && (int)a > 96) {
            // Lower case
            a = (char)((int)a - SHIFTAMT);
            if ((int)a < 97) a = (char)((int)a + 26); // correct overshift
            output[j] = a;
            j++;
            written++;
        } else if ((int)a < 91 && (int)a > 64) {
            // Upper case
            a = (char)((int)a - SHIFTAMT);
            if ((int)a < 65) a = (char)((int)a + 26);
            output[j] = a;
            j++;
            written++;
        }
    }
    output[j] = '\0';
    fwrite(output, 1, strlen(output), stdout);
    printf("\n");
    free(input);
    free(output);
    return 0;
}
