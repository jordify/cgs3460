#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "jpeg.h"

// Takes as input a pointer to pixel data, width, height, and amount of
// bins per color and returns a three-dimensional histogram of size
// equal to bins per color per dimension
int* compute_histogram(unsigned char* pixels, int width, int height, int bins_per_color);

// Uses the JPEG library as defined in jpeg.h to decompress a jpeg image
// called filename and returns a pointer to the uncompressed pixel data
// as well as the width and height, in pixels, of the uncompressed
// image.
unsigned char* get_pixels(char* filename, int* width, int* height);

// Takes as input a three dimensional square matrix with size
// bins_per_color and writes the matrix to a file.
void write_histogram(int* histogram, int bins_per_color, char* file_name);

// Function that maps pixel values to the histogram
void classify_pixel(unsigned int red, unsigned int green, unsigned int blue, 
    int bins_per_color, int* histogram);

// Function for translating from 3-Di coordinates into a 1-D array
// index.
int arrayIndex(int x, int y, int z, int binSize);

// Debug wrapper for printf
int debugPrintf(const char *fmt, ...);
