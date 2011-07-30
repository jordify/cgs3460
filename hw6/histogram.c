#include "histogram.h"

int main(int argc, char* argv[]) {
    // Check command line input
    if (argc != 4) {
        printf("Usage: \n\t%s <input filename> <output filename> <number of bins>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int bins_per_color = atoi(argv[3]);
    int width, height;

    // Get uncompressed pixel data
    unsigned char* pixels = get_pixels(argv[1], &width, &height);

    // Compute the histogram from pixel data
    int* hist = compute_histogram(pixels, width, height, bins_per_color);

    // Write histogram to file
    write_histogram(hist, bins_per_color, argv[2]);

#ifdef DEBUG
    int i, sum;
    sum = 0;
    for (i=0; i<(bins_per_color*bins_per_color*bins_per_color); i++)
        sum += hist[i];
    debugPrintf("Sum: %d\n", sum); // Should be 65536 for Lenna.jpg
#endif

    // Free pixel data
    free(pixels);

    // Free histogram
    free(hist);

    // Exit
    return (0);
}

int* compute_histogram(unsigned char * pixels, int width, int height, int bins_per_color) {
    // First make the histogram array.
    // hist will be a 1D array, can translate from 3D coordinates to
    // array index using the arrayIndex funcion. Need calloc here to
    // ensure the ++ operator will start from zero and not random.
    int* hist = calloc(bins_per_color*bins_per_color*bins_per_color,sizeof(int));

    // Next, step through image pixel-by-pixel and analyze the colors
    int i, j;
    unsigned char blue, green, red;
    for (i=0; i<height; i++)
        for (j=0; j<width*4; j+=4) {
            // Get colors
            blue = pixels[i*j + j];
            green = pixels[i*j + j+1];
            red = pixels[i*j + j+2];
            // Alpha: do nothing

            // Classify pixel
            classify_pixel(red, green, blue, bins_per_color, hist);
        }
    
    // Return the histogram data
    return (hist);
}

void classify_pixel(unsigned int red, unsigned int green, unsigned int blue,
        int bins_per_color, int* histogram) {
    int i;
    int redBin, greenBin, blueBin; // Resulting bin location for pixel (coordinate in histogram)
    int step = 256/bins_per_color; // Step size for bins

    for (i=0; i<bins_per_color; i++) {
        // Check if each pixel is in the current range
        if (red >= i*step && red < (i+1)*step)
            // If so store current bin number for the pixel in range
            redBin = i;
        if (green >= i*step && green < (i+1)*step)
            greenBin = i;
        if (blue >= i*step && blue < (i+1)*step)
            blueBin = i;
    }
    // Increment the histogram value at the bin coordinates
    histogram[arrayIndex(blueBin, greenBin, redBin, bins_per_color)]++;
}

unsigned char* get_pixels(char* filename, int* width, int* height) {
    // Uncompress the desired JPEG file
    int rc = loadJPG(filename, "temp.bmp");
    debugPrintf("Return of loadJPG call=%d\n", rc);

    // Open temp.bmp to read pixel data
    FILE *bmpFile;
    bmpFile = fopen("temp.bmp", "rb");
    if (bmpFile == NULL) {
        printf("Failed to open %s!\n", "temp.bmp");
        exit(EXIT_FAILURE);
    }

    // Seek to beginning of file
    fseek(bmpFile, 0L, SEEK_SET);

    // Get width and height
    fread(width, sizeof(int), 1, bmpFile);
    fread(height, sizeof(int), 1, bmpFile);

    debugPrintf("Width: %d, Height: %d\n", *width, *height);

    // Allocate pixel data memory
    unsigned char* pixels = malloc((*width)*(*height)*4*sizeof(char));

    // Read in pixels
    rc = fread(pixels, sizeof(char), (*width)*(*height)*4, bmpFile);
    debugPrintf("Read %d chars from bmpFile\n", rc);

    // Close temp.bmp
    fclose(bmpFile);

    // Delete temp.bmp
    remove("temp.bmp");

    // Return the pointer to the data
    return (pixels);
}

void write_histogram(int* histogram, int bins_per_color, char* file_name) {
    // Open output file
    FILE* output = fopen(file_name, "w");
    if (output == NULL) {
        printf("Could not open %s for writing!\n", file_name);
        exit(EXIT_FAILURE);
    }
    
    // Write histogram data
    int block, line, point;
    for (block=0; block<bins_per_color; block++) {
        for (line=0; line<bins_per_color; line++) {
            for (point=0; point<bins_per_color; point++)
                fprintf(output, "%d,",histogram[arrayIndex(block,line,point,bins_per_color)]);
            fprintf(output, "\n");
        }
        fprintf(output, "\n");
    }

    // Close output file
    fclose(output);
}

int arrayIndex(int x, int y, int z, int binSize) {
    return (x*binSize*binSize + y*binSize + z);
}

int debugPrintf(const char *fmt, ...) {
    // Wrapper for printf
    // This function will only print if the DEBUG flag is set. It can be
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
