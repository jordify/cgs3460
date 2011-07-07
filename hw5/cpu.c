#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MEM_WIDTH 8
#define MEM_SIZE 32
#define OPCODE_SIZE 3

int pc = 0; // Program Counter
char ir[MEM_WIDTH+1]; // Instruction Register
char ac[MEM_WIDTH+1]; // Accumulator
char memory[MEM_SIZE][MEM_WIDTH+1]; // Memory

// Sets the memory to some default content
void set_memory();

// Reads the memory from keyboard
void read_memory();

// Prints the memory on screen
void print_memory();

// Converts an integer from decimal to binary, represented as a
// null-terminated string.  The result is always represented on
// MEM_WIDTH bits.
void dec2bin(int dec, char *bin);

// Converts an integer from binary, represented as a null-terminated
// string, to decimal. The string can have any length (up to MEM_WIDTH),
// depending on the position of the null character.
int bin2dec(char *bin);

// Executes the program in memory
void execute();

// Debug wrapper for printf
int debugPrintf(const char *fmt, ...);

int main(int argc, char* argv[]) {
    // Check cli, print usage if argv[1] not present
    if (argc != 2) {
        printf("Usage: %s [read memory]\n\tIf read memory != 0, user \
will provide the value of the instruction/data memory.\n\tIf read \
memory == 0, the defaults will be used.\n", argv[0]);
        return (1);
    }
    if (atoi(argv[1])==0)
        set_memory(); // If 0, set memory
    else
        read_memory(); // Otherwise, read memory

    // Execute
    execute();

    // Print Memory
    print_memory();

    // Print ac
    printf("Acumulator: \n");
    puts(ac);
    printf("\n");

    return (0);
}

void set_memory() {
    strcpy(memory[0], "01101011\0");
    strcpy(memory[1], "10001101\0");
    strcpy(memory[2], "01001011\0");
    strcpy(memory[3], "01100001\0");
    strcpy(memory[4], "10100001\0");
    strcpy(memory[5], "01000001\0");
    strcpy(memory[6], "01101100\0");
    strcpy(memory[7], "11100001\0");
    strcpy(memory[8], "01001100\0");
    strcpy(memory[9], "00100000\0");
    strcpy(memory[10], "00000000\0");
    strcpy(memory[11], "00000000\0");
    strcpy(memory[12], "00000011\0");
    strcpy(memory[13], "00000010\0");
    strcpy(memory[14], "00000100\0");
    strcpy(memory[15], "00000101\0");
    strcpy(memory[16], "00000000\0");
    strcpy(memory[17], "00000000\0");
    strcpy(memory[18], "00000000\0");
    strcpy(memory[19], "00000000\0");
    strcpy(memory[20], "00000000\0");
    strcpy(memory[21], "00000000\0");
    strcpy(memory[22], "00000000\0");
    strcpy(memory[23], "00000000\0");
    strcpy(memory[24], "00000000\0");
    strcpy(memory[25], "00000000\0");
    strcpy(memory[26], "00000000\0");
    strcpy(memory[27], "00000000\0");
    strcpy(memory[28], "00000000\0");
    strcpy(memory[29], "00000000\0");
    strcpy(memory[30], "00000000\0");
    strcpy(memory[31], "00000000\0");
}

void read_memory() {
    int i = 0;
    char* rc;
    int len;
    char temp[MEM_WIDTH+1];

    printf("==============================\n");
    printf("Enter Values (Ctr-d will zero out the rest):\n");
    for (; i < MEM_SIZE; i++) {
        printf("memory[%d]: ", i);
        rc = fgets(temp, MEM_WIDTH+2, stdin);
        if (rc == NULL) // An error or EOF
            break;
        else {
            len = strlen(temp);
            if (len <= MEM_WIDTH) { // Fix if input is less than MEM_WIDTH
                strncpy(memory[i], temp, len-1);
                int j;
                for (j = len-1; j < MEM_WIDTH; j++)
                    memory[i][j] = '0'; // Zero all bits not specified by user
            } else {
                // copy the first 8 bits to memory
                strncpy(memory[i], temp, MEM_WIDTH);
            }
            memory[i][MEM_WIDTH] = '\0'; // Always add null bit
        }
    }

    // If an error or EOF occured, zero out the rest of the memory
    if (i < MEM_SIZE)
        for (; i < MEM_SIZE; i++)
            strcpy(memory[i], "00000000\0");
    printf("\n==============================\n");
}

void print_memory() {
    int i = 0;

    printf("==============================\n");
    printf("Memory Values:\n");

    for (; i < MEM_SIZE; i++) {
        printf("memory[%d]: ", i);
        puts(memory[i]);
    }

    printf("==============================\n");
}

void dec2bin(int dec, char *bin) {
    int i;
    for (i = MEM_WIDTH-1; i >= 0; i--) {
        *(bin+i) = (char) ('0'+(dec % 2));
        dec /= 2;
    }
    *(bin+MEM_WIDTH) = '\0';
}

int bin2dec(char *bin) {
    int i, rc, len;
    len = strlen(bin);

    rc = 0;
    for (i = 0; i < len; i++) {
        if (*(bin+i)=='1')
            rc += pow(2,(len-1)-i);
    }
    return (rc);
}

void execute() {
    char inst[4] = {'\0'};
    int x;

    while (1) {
        debugPrintf("==============================\n");
        debugPrintf("pc=%d\n", pc);
        debugPrintf("ac=0b%s\n",ac);

        // Load instruction into IR
        strcpy(ir, memory[pc]);

        // Increment the pc
        pc++;

        // Get instruction
        strncpy(inst, ir, 3);
        
        // Perform the instruction
        if (strcmp(inst,"000")==0) {
            debugPrintf("Halt\n");
            break;
        }
        else if (strcmp(inst,"001")==0) {
            debugPrintf("JANZ\n");
            if(bin2dec(ac)!=0)
                pc = bin2dec(ir+3);
        }
        else if (strcmp(inst,"010")==0) {
            debugPrintf("StAM\n");
            strcpy(memory[bin2dec(ir+3)], ac);
        }
        else if (strcmp(inst,"011")==0) {
            debugPrintf("LdAM\n");
            strcpy(ac, memory[bin2dec(ir+3)]);
        }
        else if (strcmp(inst,"100")==0) {
            debugPrintf("AddM\n");
            x = bin2dec(ac) + bin2dec(memory[bin2dec(ir+3)]);
            dec2bin(x, ac);
        }
        else if (strcmp(inst,"101")==0) {
            debugPrintf("AddI\n");
            x = bin2dec(ac) + bin2dec(ir+3);
            dec2bin(x, ac);
        }
        else if (strcmp(inst,"110")==0) {
            debugPrintf("SubM\n");
            x = bin2dec(ac) - bin2dec(memory[bin2dec(ir+3)]);
            dec2bin(x, ac);
        }
        else if (strcmp(inst,"111")==0) {
            debugPrintf("SubI\n");
            x = bin2dec(ac) - bin2dec(ir+3);
            dec2bin(x, ac);
        }
        else {
            debugPrintf("NAN\n");
            break;
        }
    }
}

int debugPrintf(const char *fmt, ...) {
    // Wrapper for printf
    // This function Will only print if the DEBUG flag is set. It can be
    // set by adding "-DDEBUG" to the gcc argument list.
    int rc = 0;
#ifdef DEBUG
    va_list args;
    va_start(args, fmt);
    rc = vprintf(fmt,args);
    va_end(args);
#endif
    return (rc);
}
