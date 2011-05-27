#include <stdio.h>

void takeInput(int* a, int* b, int* c, int* d) {
    printf("Enter number: ");
    scanf("%d + %d i", a, b);
    printf("Enter number: ");
    scanf("%d + %d i", c, d);
    printf("\n");
}

int main() {
    int choice = 0;
    int a, b, c, d;

    printf("Complex Number Calculator\n\n");
    while (1) {
        printf("Available Options:\n0 - exit\n");
        printf("1 - add\n2 - subtract\n3 - multiply\n4 - divide\n\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                takeInput(&a, &b, &c, &d);
                printf("Result: %f+%fi\n\n", (float)a+c, (float)b+d);
                break;
            case 2:
                takeInput(&a, &b, &c, &d);
                printf("Result: %f+%fi\n\n", (float)a-c, (float)b-d);
                break;
            case 3:
                takeInput(&a, &b, &c, &d);
                printf("Result: %f+%fi\n\n", (float)(a*c-b*d), (float)(a*d+b*c));
                break;
            case 4:
                takeInput(&a, &b, &c, &d);
                if (c==0 && d==0)
                    printf("Undefined\n\n");
                else
                    printf("Result: %f+%fi\n\n", (float)(a*c+b*d)/(c*c+d*d), (float)(b*c-a*d)/(c*c+d*d));
                break;
            default:
                return 0;
        }
    }
    return 0;
}
