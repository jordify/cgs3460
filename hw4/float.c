#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Converts exponent from binary to decimal.
int bin2dec(char binary[]);

// Converts exponent from decimal to binary.
void dec2bin(int decimal, char binary[]);

/* 
 * Forms a floating-point number in mantissa-exponent representation
 * from two arrays, one representing the mantissa and the other the
 * exponent. The first array is of size 23, the second one 8, and the
 * third 32.
 */
void gather(char mantissa[], char exponent[], char mantissa_exponent[]);

// Converts a double to mantissa-exponent representation.
void convert(double x, char mantissa_exponent[]);

/* 
 * Converts a floating point number from mantissa-exponent
 * representation to a double.
 */
double convert_back(char mantissa_exponent[]);

// Shifts the mantissa a number of postions to the right
void shift(char mantissa[], int n_pos);

/*
 * Aligns the mantissa of two numbers so that they have the same
 * exponent (the larger of the two) and returns the exponent.
 */
int align(int exp1, char mantissa1[], int exp2, char mantissa2[]);

// Adds two numbers in mantissa-exponent representation
void add(char x1[], char x2[], char result[]);

// Shift left used during convert
void shiftl(char mantissa[], int n_pos);

// Print the number and its binary representation
void pprint(double x, char x1[]);

// Unit tests used during development.
void runTests(void);

int main(int argc, char* argv[]) {
    if (argc > 1)
        runTests();
    else {
        char x1[32] = {(char)0};
        char x2[32] = {(char)0};
        char result[32] = {(char)0};
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;

        // Get input
        printf("Enter x1: ");
        scanf("%lf", &x);
        printf("Enter x2: ");
        scanf("%lf", &y);
        printf("\n");
        
        // Convert the inputs to binary
        convert(x, x1);
        convert(y, x2);

        // Perform the addition
        add(x1, x2, result);
        z = x + y;

        // Print the emulation
        pprint(x, x1);
        printf("\n+ ");
        pprint(y, x2);
        printf("\n----------------------------------------\n");
        pprint(z, result);
        printf("\n");
    }
    return (0);
}

int bin2dec(char binary[]) {
    int i;
    int result = 0;
    for (i = 0; i<8; i++)
        if (binary[i]==1)
            result += pow(2,7-i);
    return result;
}

void dec2bin(int decimal, char binary[]) {
    int i;
    for (i = 0; i<8; i++) {
        binary[7-i] = (char) (decimal % 2);
        decimal = decimal / 2;
    }
}

void gather(char mantissa[], char exponent[], char mantissa_exponent[]) {
    int i = 1;
    for(; i < 9; i++) 
        mantissa_exponent[i] = exponent[i-1];
    for (; i < 32; i++)
        mantissa_exponent[i] = mantissa[i-9];
}

void split(char mantissa_exponent[], char mantissa[], char exponent[]) {
    int i;
    for (i = 1; i < 9; i++)
        exponent[i-1] = mantissa_exponent[i];
    for (; i < 32; i++)
        mantissa[i-9] = mantissa_exponent[i];
}

void convert(double x, char mantissa_exponent[]) {
    int i;
    char mantissa[23] = {(char)0};
    char exponent[8] = {(char)0};

    // Calculate sign bit first
    if (x < 0) {
        mantissa_exponent[0] = 1;
        x *= -1;
    } else
        mantissa_exponent[0] = 0;
    
    // Seperate the decimal and fractional parts
    int decPart = (int) x;
    double fracPart = x - decPart;

    // Conver the decimal part to binary, put it at the end of the array
    for (i = 0; decPart >= 1; i++) {
        mantissa[22-i] = (char) (decPart % 2);
        decPart = decPart / 2;
    }
    i--;
    int exp = i;

    // Shift mantissa to left 22-exp
    shiftl(mantissa, 22-exp);

    // Put exponent in mantissa_exponent array
    dec2bin(exp, exponent);

    // Deal with fractional part
    if (fracPart != 0.0) {
        i = exp+1; // Current position in mantissa
        for (; i < 32; i++) {
            fracPart = fracPart * 2;
            mantissa[i] = (char) ((int)fracPart);
            fracPart -= (int)fracPart;
        }
    }

    // Gather result
    gather(mantissa, exponent, mantissa_exponent);
}

double convert_back(char mantissa_exponent[]) {
    int i;
    double result = 0.0;
    char exponent[8] = {(char)0};
    char mantissa[23] = {(char)0};

    // Split mantissa_exponent
    split(mantissa_exponent, mantissa, exponent);

    // Get exponent
    int exp = bin2dec(exponent);

    // exp+1 first digits in mantissa represent decPart
    for (i = 0; i < exp+1; i++)
        if (mantissa[i] == (char)1)
            result += pow(2, exp-i);

    // Remaining digits in mantissa represent fracPart pow(2,negative number)
    for (; i < 23; i++)
        if (mantissa[i] == (char)1)
            result += pow(2, exp-i);

    // Return the result * -1^signBit
    if (mantissa_exponent[0] == (char)1)
        return result*-1;
    else
        return result;
}

void shiftl(char mantissa[], int n_pos) {
    int i;

    // Shift left n_pos
    for (i = n_pos; i < 23; i++) 
        mantissa[i-n_pos] = mantissa[i];

    // Zero out the rest of the array
    for (i -= n_pos; i < 23; i++)
        mantissa[i] = (char) 0;
}

void shift(char mantissa[], int n_pos) {
    int i;

    // Shift right n_pos
    for (i = 22; i >= n_pos; i--) 
        mantissa[i] = mantissa[i-n_pos];

    // Zero out the rest of the array
    for (i = 0; i < n_pos; i++)
        mantissa[i] = (char) 0;
}

int align(int exp1, char mantissa1[], int exp2, char mantissa2[]) {
    // If equal, don't do anything
    if (exp1 == exp2)
        return (exp1);
    // Else, shift right the lesser by the difference and return the new
    // exponent.
    else {
        if (exp1 > exp2) {
            int diff = exp1-exp2;
            shift(mantissa2, diff);
            return (exp1);
        } else {
            int diff = exp2-exp1;
            shift(mantissa1, diff);
            return (exp2);
        }
    }
}

void add(char x1[], char x2[], char result[]) {
    char man1[23] = {(char)0};
    char man2[23] = {(char)0};
    char resMan[23] = {(char)0};
    char resExp[8] = {(char)0};
    char tmpExp[8] = {(char)0};
    int exp1, exp2, i;

    // Split the result
    split(result, resMan, resExp);

    // Split x1, get exp1
    split(x1, man1, tmpExp);
    exp1 = bin2dec(tmpExp);

    // Split x2, get exp2
    split(x2, man2, tmpExp);
    exp2 = bin2dec(tmpExp);

    // Align the two mantissas
    int bigExp = align(exp1, man1, exp2, man2);

    // Write the result exponent
    dec2bin(bigExp, resExp);

    // Add the mantissas 
    int tmp = 0;
    int rem = 0;
    for (i = 22; i >= 0; i--) {
        tmp = (int) man1[i] + (int) man2[i] + rem;
        if (tmp == 3) {
            rem = 1;
            resMan[i] = (char) 1;
        } else if (tmp == 2) {
            rem = 1;
            resMan[i] = (char) 0;
        } else if (tmp == 1) {
            rem = 0;
            resMan[i] = (char) 1;
        } else if (tmp == 0) {
            rem = 0;
            resMan[i] = (char) 0;
        }
    }

    // Gather the result
    result[0] = (char) 0; // Assuming always positive, as per the hw document
    gather(resMan, resExp, result);
}

void pprint(double x, char x1[]) {
    int i = 0;
    printf("%4.5g: ", x);
    printf("%1d ", (int) x1[i]);
    for (; i < 9; i++)
        printf("%1d", (int) x1[i]);
    printf(" ");
    for (; i < 32; i++)
        printf("%1d", (int) x1[i]);
}

void runTests(void) {
    /* Test bin2dec {{{ */
    int x;
    char z[8] = {0,0,0,0,0,1,1,0};
    x = bin2dec(z);
    if (x != 6)
        printf("\nbin2dec Test Failure: %d != 8\n", x);
    else
        printf("|");
    char y[8] = {1,1,1,1,1,1,1,1};
    x = bin2dec(y);
    if (x != 255)
        printf("bin2dec Test Failure: %d != 255\n", x);
    else
        printf(".");
    char v[8] = {1,0,1,0,1,0,1,0};
    x = bin2dec(v);
    if (x != 170)
        printf("bin2dec Test Failure: %d != 255\n", x);
    else
        printf(".");
    // }}}

    /* Test dec2bin {{{ */
    int i;
    int fail = 0;
    char testResult[8] = {0};
    dec2bin(255, testResult);
    for (i = 0; i < 8; i++)
        if ((int)testResult[i] == 0)
            fail = 1;
    if (fail) {
        printf("dec2bin Test Failure: ");
        for (i = 0; i < 8; i++)
            printf("%d", (int)testResult[i]);
        printf(" != 11111111\n");
    }
    else
        printf("|");
    fail = 0;
    dec2bin(0, testResult);
    for (i = 0; i < 8; i++)
        if ((int)testResult[i] == 1)
            fail = 1;
    if (fail) {
        printf("dec2bin Test Failure: ");
        for (i = 0; i < 8; i++)
            printf("%d", (int)testResult[i]);
        printf(" != 00000000\n");
    }
    else
        printf(".");
    fail = 0;
    dec2bin(85, testResult);
    for (i = 0; i < 8; i++)
        if ((int)testResult[i] != i%2)
            fail = 1;
    if (fail) {
        printf("dec2bin Test Failure: ");
        for (i = 0; i < 8; i++)
            printf("%d", (int)testResult[i]);
        printf(" != 01010101\n");
    }
    else
        printf(".");
    fail = 0;
    dec2bin(170, testResult);
    for (i = 0; i < 8; i++)
        if ((int)testResult[i] == i%2)
            fail = 1;
    if (fail) {
        printf("dec2bin Test Failure: ");
        for (i = 0; i < 8; i++)
            printf("%d", (int)testResult[i]);
        printf(" != 10101010\n");
    }
    else
        printf(".");
    // }}}

    /* Test gather {{{ */
    char a[32] = {0};
    char exponent[8] = {1,0,1,0,1,0,1,0};
    char mantissa[23] = {1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0};
    char gathered[32] = {0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0};
    gather(mantissa, exponent, a);
    fail = 0;
    for (i = 0; i < 32; i++)
        if (a[i] != gathered[i])
            fail = 1;
    if (fail) {
        printf("gather Test Failure: ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) a[i]);
        printf(" != ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) gathered[i]);
        printf("\n");
    } else
        printf("|");
    // }}}

    /* Test split {{{ */
    char expRes[8] = {0};
    char manRes[23] = {0};
    split(gathered, manRes, expRes);
    fail = 0;
    for (i = 0; i < 8; i++)
        if (expRes[i] != exponent[i])
            fail = 1;
    for (i = 0; i < 23; i++)
        if (manRes[i] != mantissa[i])
            fail = 1;
    if (fail)
        printf("split Test Failure\n");
    else
        printf("|");
    // }}}
    
    /* Test shiftl {{{ */
    char unshifted[23] = {1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0};
    char shifted[23] = {0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0};
    shiftl(unshifted, 4);
    fail = 0;
    for (i = 0; i < 23; i++)
        if (unshifted[i] != shifted[i])
            fail = 1;
    if (fail) {
        printf("shiftl Test Failure: ");
        for (i = 0; i < 23; i++)
            printf("%d", (char) unshifted[i]);
        printf(" != ");
        for (i = 0; i < 23; i++)
            printf("%d", (char) shifted[i]);
        printf("\n");
    } else
        printf("|");
    // }}}

    /* Test shift {{{ */
    char unshifted1[23] = {1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0};
    char shifted1[23] = {0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1};
    shift(unshifted1, 4);
    fail = 0;
    for (i = 0; i < 23; i++)
        if (unshifted1[i] != shifted1[i])
            fail = 1;
    if (fail) {
        printf("shift Test Failure: ");
        for (i = 0; i < 23; i++)
            printf("%d", (char) unshifted1[i]);
        printf(" != ");
        for (i = 0; i < 23; i++)
            printf("%d", (char) shifted1[i]);
        printf("\n");
    } else
        printf("|");
    // }}}

    /* Test convert {{{*/
    char pi[32] = {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,0,0,0,1,1,1,1,1,1,0,1,1,0,1};
    char oneHundred[32] = {0,0,0,0,0,0,1,1,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char one[32] = {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char negOne[32] = {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char negTwo[32] = {1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    fail = 0;
    convert(3.141592654, a);
    for (i = 0; i < 32; i++)
        if (a[i] != pi[i])
            fail = 1;
    if (fail) {
        printf("convert Test Failure: ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) a[i]);
        printf(" != ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) pi[i]);
        printf("\n");
    } else
        printf("|");
    fail = 0;
    convert(100.0, a);
    for (i = 0; i < 32; i++)
        if (a[i] != oneHundred[i])
            fail = 1;
    if (fail) {
        printf("convert Test Failure: ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) a[i]);
        printf(" != ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) oneHundred[i]);
        printf("\n");
    } else
        printf(".");
    fail = 0;
    convert(1.0, a);
    for (i = 0; i < 32; i++)
        if (a[i] != one[i])
            fail = 1;
    if (fail) {
        printf("convert Test Failure: ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) a[i]);
        printf(" != ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) one[i]);
        printf("\n");
    } else
        printf(".");
    fail = 0;
    convert(-1.0, a);
    for (i = 0; i < 32; i++)
        if (a[i] != negOne[i])
            fail = 1;
    if (fail) {
        printf("convert Test Failure: ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) a[i]);
        printf(" != ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) negOne[i]);
        printf("\n");
    } else
        printf(".");
    fail = 0;
    convert(-2.0, a);
    for (i = 0; i < 32; i++)
        if (a[i] != negTwo[i])
            fail = 1;
    if (fail) {
        printf("convert Test Failure: ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) a[i]);
        printf(" != ");
        for (i = 0; i < 32; i++)
            printf("%d", (char) negTwo[i]);
        printf("\n");
    } else
        printf(".");
    // }}}

    /* Test convert_back {{{ */
    fail = 0;
    double oot = convert_back(oneHundred);
    if (oot != 100.0)
        printf("convert_back Test Failure: %g != 100.0\n", oot);
    else
        printf("|");
    oot = convert_back(one);
    if (oot != 1.0)
        printf("convert_back Test Failure: %g != 1.0\n", oot);
    else
        printf(".");
    oot = convert_back(negOne);
    if (oot != -1.0)
        printf("convert_back Test Failure: %g != -1.0\n", oot);
    else
        printf(".");
    oot = convert_back(negTwo);
    if (oot != -2.0)
        printf("convert_back Test Failure: %g != -1.0\n", oot);
    else
        printf(".");
    oot = convert_back(pi);
    if (oot <= 3.141592654*0.9 || oot >= 3.141592654*1.1)
        printf("convert_back Test Failure: %1.100g != 3.141592654\n", oot);
    else
        printf(".");
    // }}}
    
    /* Test align {{{ */
    int exp1 = 3;
    int exp2 = 1;
    char man1[23] = {1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0};
    char man2[23] = {0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1};
    char res1[23] = {1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0};
    char res2[23] = {0,0,0,0, 0,0,1,1, 1,1,0,0, 0,0,1,1, 1,1,0,0, 0,0,1};
    fail = 0;
    align(exp1, man1, exp2, man2);
    for (i = 0; i < 23; i++)
        if (man1[i] != res1[i] || man2[i] != res2[i])
            fail = 1;
    if (fail) {
        printf("align Test Failure: ");
        for (i = 0; i < 23; i++)
            printf("%d", (char) man2[i]);
        printf(" != ");
        for (i = 0; i < 23; i++)
            printf("%d", (char) res2[i]);
        printf("\n");
    } else
        printf("|");
    // }}}

    /* Clean up */
    printf("\n");
}
