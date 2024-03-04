/* This coursework specification, and the example code provided during the
 * course, is Copyright 2024 Heriot-Watt University.
 * Distributing this coursework specification or your solution to it outside
 * the university is academic misconduct and a violation of copyright law. */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The RGB values of a pixel. */
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/* An image loaded from a file. */
struct Image {
    /* TODO: Question 1 */
    //char format;
    char file_type[3];
    int width;
    int height;
    struct Pixel *pixelArray;
};

/* Free a struct Image */
void free_image(struct Image *img)
{
    /* TODO: Question 2a */
    free(img);
}

/* Opens and reads an image file, returning a pointer to a new struct Image.
 * On error, prints an error message and returns NULL. */
struct Image *load_image(const char *filename)
{
    fprintf(stdout, "->load_image initiated \n");
    /* Open the file for reading */
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return NULL;
    }

    /* Allocate the Image object, and read the image from the file */
    /* TODO: Question 2b */
    struct Image *Image = malloc(sizeof(struct Image));
    if (Image == NULL) {
        fprintf(stderr, "Image failed to allocate memory");

        return NULL;
    }


    //scans header
    if (fscanf(f, "%3s", &Image->file_type) != 1) {
        fprintf(stderr, "File Header couldn't be read %s\n", filename);
        fclose(f);
        return NULL;
    }
    fprintf(stdout, "Image Type %s\n", Image->file_type);

    if (fscanf(f, "%d", &Image->width) != 1) {
        fprintf(stderr, "File Width couldn't be read %s\n", filename);
        fclose(f);
        return NULL;
    }
    fprintf(stdout, "Image Width %d\n", Image->width);

    if (fscanf(f, "%d", &Image->height) != 1) {
        fprintf(stderr, "File Height couldn't be read %s\n", filename);
        fclose(f);
        return NULL;
    }
    fprintf(stdout, "Image Height %d\n", Image->height);

    //kills \n's
    fgetc(f);

    //allocates memory dynamically based off of header values
    Image->pixelArray = (struct Pixel *)malloc(Image->width * Image->height * sizeof(struct Pixel));
    if (Image->pixelArray == NULL) {
        // Handle memory allocation failure
        fprintf(stderr, "PixelArray failed to allocate memory");
        free(Image); // Free previously allocated memory
        return NULL;
    }


    //attempt to assign pixels from fread
    for (int i = 0; i < (Image->height * Image->width); i++) {
        if (fread(&Image->pixelArray[i].red, sizeof(unsigned char), 1, f) != 1 ||
            fread(&Image->pixelArray[i].green, sizeof(unsigned char), 1, f) != 1 ||
            fread(&Image->pixelArray[i].blue, sizeof(unsigned char), 1, f) != 1) {
            fprintf(stderr, "Error reading pixel data.\n");
            fclose(f);
            free(Image->pixelArray); // Free allocated memory
            free(Image);             // Free allocated memory
            return NULL;
        }
    }


/*
    char data[9];
    size_t bytes_read;
    for (int i = 0; i <3; i++) {
        bytes_read = fread(data, 1, 8, f);
        if (bytes_read != 8) {
            fprintf(stdout, "error reading line %d \n", i + 1);
            break;
    }
    data[8] = '\0';
    fprintf(stdout, "Line %d: %s\n", i+1, data);    
}
*/
/*
    if (fread(&data, sizeof(unsigned char), 1, f) != 8) {
        fprintf(stderr, "File data couldn't be read %d\n", f);
        fclose(f);
        return(NULL);
    }
    for (int i = 7; i >= 0; i--) {
        printf("%d \n", (data >> i) & 1);
    }
*/


    //allocates space based on read header
    //Image.pixelArray = (struct Pixel)malloc();


    /* Close the file */
    fclose(f);

    if (Image == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }
    fprintf(stdout, "->load_image complete \n");
    return Image;
}

/*
void printPixelValues(struct Image *image) {
    for (int i = 0; i < (image->height * image->width); i++) {
        printf("Pixel:%d-R%dG%dB%d\n",
               i+1, image->pixelArray[i].red,
               image->pixelArray[i].green, image->pixelArray[i].blue);
    }
}
*/


/* Write img to file filename. Return true on success, false on error. */
bool save_image(const struct Image *img, const char *filename)
{
    fprintf(stdout, "->save_image initiated \n");
    /* TODO: Question 2c */
    //takes image structure and parses through as it writes data to a file using 
    FILE *f = fopen(filename, "wb");
    fprintf(stdout, "file opened successfully \n");
    
    fprintf(f, "%s\n", img->file_type);
    fprintf(stdout, "file_type written: %s \n", img->file_type);
    
    fprintf(f, "%d ", img->width);
    fprintf(stdout, "width written: %d \n", img->width);
    
    fprintf(f, "%d\n", img->height);
    fprintf(stdout, "height written: %d \n", img->height);
    //this is shoddily put together, must be made robust ^^^^

//  fprintf(NameOfFilePointer, "%d", myIntegerVariableName);
//  ^^^^^^^
//  optimal data writing format for non-binary/ascii data
//  as fwrite is explicitly for binary data
//  similar to fscan/fread paradigm

    //now the grunt work: writing binary data from IMAGE struct with fwrite
    /* ATTEMPT1, with fwrite
    for (int i = 0; i < (img->width * img->height); i++) {
        fprintf(stdout, "pixel:%d \n", i);
        fwrite(img->pixelArray[i].red, sizeof(unsigned char), 1, f);
        fprintf(stdout, "pixel:%d \n", i);
        fwrite(img->pixelArray[i].blue, sizeof(unsigned char), 1, f);
        fwrite(img->pixelArray[i].green, sizeof(unsigned char), 1, f);
    }
    */
   
   // ATTEMPT2, uses fprintf to print decimals
    for (int i = 0; i < (img->width * img->height); i++) {
        if (fprintf(f, "%c", img->pixelArray[i].red) != 1 ||
        fprintf(f, "%c", img->pixelArray[i].green) != 1 ||
        fprintf(f, "%c", img->pixelArray[i].blue) != 1 ) {

        fprintf(stderr, "failed to save pixel data on pixel:%d \n", i);
        return false;
        }
    }

    // PIXEL DATA IS CONVERTED TO CHARACTERS OF DECIMAL INTS, THUS I NEED TO EITHER CAST THEM HERE  OR  


    fclose(f);

    //implement error returns on wites and saves
    fprintf(stdout, "->save_image complete \n");
    return true;
}

/* Allocate a new struct Image and copy an existing struct Image's contents
 * into it. On error, returns NULL. */
struct Image *copy_image(const struct Image *source)
{
    /* TODO: Question 2d */
    struct Image *img_copy = malloc(sizeof(*source));
    
    img_copy = source;

    img_copy->pixelArray = (struct Pixel *)malloc(sizeof(source->pixelArray));

    for (int i = 0; i < (img_copy->width * img_copy->height); i++){
        img_copy->pixelArray[i].red = source->pixelArray[i].red;
        //fprintf(stdout, "red%d: %c, %c \n", i, img_copy->pixelArray[i].red, source->pixelArray[i].red);

    }


    free(img_copy);
    free(img_copy->pixelArray);
    return NULL;
}

/* Perform your first task.
 * (TODO: Write a better comment here, and rename the function.
 * You may need to add or change arguments depending on the task.)
 * Returns a new struct Image containing the result, or NULL on error. */
struct Image *apply_MEDIAN(const struct Image *source)
{
    /* TODO: Question 3 */
    return NULL;

    //pointer at a pixel changes colour value, to median of the 4 adjacent pixels, above/below/right/left
    //excluding nonexistent pixels, when at edges



}

/* Perform your second task.
 * (TODO: Write a better comment here, and rename the function.
 * You may need to add or change arguments depending on the task.)
 * Returns true on success, or false on error. */
bool apply_NORM(const struct Image *source)
{
    /* TODO: Question 4 */
    return false;

    //scan for min and max for each colour values in the image
    //subtract the offset minimums, to 0
    //then multiply all values by a scaling factor so the max values are scaled to the max possible values


}

int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    /* TODO: Remove this if you don't need to use rand() */
    srand(time(NULL));

    /* Check command-line arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: process INPUTFILE OUTPUTFILE\n");
        return 1;
    }

    /* Load the input image */
    struct Image *in_img = load_image(argv[1]);
    if (in_img == NULL) {
        return 1;
    }

    if (!save_image(in_img, argv[2])) {
        fprintf(stderr, "saving image failed \n");
    }
    
    // printPixelValues(in_img);

    copy_image(in_img);





    /* Apply the first process */
    struct Image *out_img = apply_MEDIAN(in_img);
    if (out_img == NULL) {
        fprintf(stderr, "First process failed.\n");
        free_image(in_img);
        return 1;
    }

    /* Apply the second process */
    if (!apply_NORM(out_img)) {
        fprintf(stderr, "Second process failed.\n");
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    /* Save the output image */
    if (!save_image(out_img, argv[2])) {
        fprintf(stderr, "Saving image to %s failed.\n", argv[2]);
        free_image(in_img);
        free_image(out_img);
        return 1;
    }

    free_image(in_img);
    free_image(out_img);
    return 0;
}
