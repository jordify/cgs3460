#include <stdio.h>

int main() {
    int n, i, j;
    printf("Number of lines in triangle: ");
    scanf("%d", &n);
    printf("\n");
    for (i = 0; i<n; i++) {
        if (i==n-1){
            int astrisks;
            for (astrisks=0; astrisks<(n*2-1); astrisks++)
                printf("*");
            printf("\n");
        } else {
            int spaces;
            int innerSpaces;
            spaces = (n-1)-i;
            innerSpaces = i*2-1;
            if (i==0) {
                for (j=0; j<spaces; j++)
                    printf(" ");
                printf("*\n");
            } else {
                for (j=0; j<spaces; j++)
                    printf(" ");
                printf("*");
                for (j=0; j<innerSpaces; j++)
                    printf(" ");
                printf("*\n");
            }
        }
    }
    printf("\n");
    return 0;
}
