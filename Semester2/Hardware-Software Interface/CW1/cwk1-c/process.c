/*
    HS CW1
    Calum Murray
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// structures

/* The RGB values of a pixel. */
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/* An image loaded from a file. */
struct Image {
    char file_type[4];
    int width;
    int height;
    struct Pixel *pixelArray;
};



// auxillary functions

/* compares 2 values, used for qsort() function */
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}   

/* test function that prints every rgb value for every pixel in an image */
void printPixelValues(struct Image *image) {
    for (int i = 0; i < (image->height * image->width); i++) {
        printf("Pixel:%d-R%dG%dB%d\n",
               i+1, image->pixelArray[i].red,
               image->pixelArray[i].green, image->pixelArray[i].blue);
    }
}



// CW functions

/* Free a struct Image */
void free_image(struct Image *img)
{
    //frees the memory of the Image stucture
    free(img);
    //and frees the memory for the array of the Pixel substructure
    free(img->pixelArray);
}

/* Opens and reads an image file, returning a pointer to a new struct Image.
 * On error, prints an error message and returns NULL. */
struct Image *load_image(const char *filename)
{
    //opens the file to be read with read and binary options
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return NULL;
    }


        //allocates the memory for the Image
        struct Image *in_img = malloc(sizeof(struct Image));
        if (in_img == NULL) {
            fprintf(stderr, "Image failed to allocate memory");
            return NULL;
        }


        //scans the image format from the image file, saving it to in_img->file_type
        if (fscanf(f, "%s", in_img->file_type) != 1) {
            fprintf(stderr, "File Header couldn't be read %s\n", filename);
            fclose(f);
            return NULL;
        }
        //scans the width
        if (fscanf(f, "%d", &in_img->width) != 1) {
            fprintf(stderr, "File Width couldn't be read %s\n", filename);
            fclose(f);
            return NULL;
        }
        //scans the height
        if (fscanf(f, "%d", &in_img->height) != 1) {
            fprintf(stderr, "File Height couldn't be read %s\n", filename);
            fclose(f);
            return NULL;
        }


        //gets a single character from the file, which will be the whitespace character between the header and pixel data
        fgetc(f);


        //allocates memory for the array of pixels dynamically based off of header values
        in_img->pixelArray = (struct Pixel *)malloc(in_img->width * in_img->height * sizeof(struct Pixel));
        if (in_img->pixelArray == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "PixelArray failed to allocate memory");
            free_image(in_img); // Free previously allocated memory
            return NULL; // Returns NULL as the load has failed
        }

        //loops for each pixel in the image
        for (int i = 0; i < (in_img->height * in_img->width); i++) {
            //reads in binary data from the FILE f, saving data to the address of the current Pixel rgb variables
            //if-statement handles error if the data read from fread isnt 1byte as expected
            if    (fread(&in_img->pixelArray[i].red, sizeof(unsigned char), 1, f) != 1 
                || fread(&in_img->pixelArray[i].green, sizeof(unsigned char), 1, f) != 1 
                || fread(&in_img->pixelArray[i].blue, sizeof(unsigned char), 1, f) != 1 )   
            {
                    fprintf(stderr, "Error reading pixel data.\n");
                    fclose(f);
                    free_image(in_img);  // Free allocated memory
                    return NULL;
            }
        }


    /* Close the file */
    if (fclose(f)) {
        fprintf(stderr, "error closing file %s \n", filename);
        return NULL;
    }


    //checks the in_img exists one last time before returning the Image
    if (in_img == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }

    //successful return
    return in_img;
}

/* Write img to file filename. Return true on success, false on error. */
bool save_image(const struct Image *img, const char *filename)
{
    //opens the image to be written to, with options write and binary
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return false;
    }
    

        //writes file format, width and height to the FILE f, with desired whitespace characters
        fprintf(f, "%s\n", img->file_type);
        fprintf(f, "%d ", img->width);
        fprintf(f, "%d\n", img->height);

        //for each Pixel in the Image
        for (int i = 0; i < (img->width * img->height); i++) {
            //writes binary data from im_img with fwrite, 1byte(sizeof(char)) 1 at a time
            if (  fwrite(&img->pixelArray[i].red, sizeof(unsigned char), 1, f) != 1
               || fwrite(&img->pixelArray[i].green, sizeof(unsigned char), 1, f) != 1
               || fwrite(&img->pixelArray[i].blue, sizeof(unsigned char), 1, f) != 1 )
            {       //hamdles error when writing
                    fprintf(stderr, "Error writing pixel data.\n");
                    fclose(f);
                    return false;
            }
        }


    //closes the file, catching and handling error if neccessary
    if (fclose(f)) {
        fprintf(stderr, "error closing file %s \n", filename);
        return false;
    }

    //successful save
    return true;
}

/* Allocate a new struct Image and copy an existing struct Image's contents
 * into it. On error, returns NULL. */
struct Image *copy_image(const struct Image *source)
{
    //allocates memory for the duplicate and creats an Image poointer to it
    struct Image *img_copy = malloc(sizeof(*source));
    if (img_copy == NULL) {
        fprintf(stderr, "failed to allocate memory for img_copy");
        return NULL;
    }

    //copies image format str value with strcopy() lib function
    strcpy(img_copy->file_type, source->file_type);
    //copies width/height header values
    img_copy->width = source->width;
    img_copy->height = source->height;

    //assigns memory for the duplicate pixelArray
    img_copy->pixelArray = (struct Pixel *)malloc(img_copy->width * img_copy->height * sizeof(struct Pixel));
    if (img_copy->pixelArray == NULL) {
        fprintf(stderr, "memory failed to allocate for pixelArray of img_copy");
        free_image(img_copy);
        return NULL;
    }

    //uses lib function memcpy(), to copy Pixel data from source to img_copy
    memcpy(img_copy->pixelArray, source->pixelArray, img_copy->width*img_copy->height*sizeof(struct Pixel));

    //successful copy
    return img_copy;
}

/* Perform your first task.
 * Applies median value of each adjacent pixel to every pixel in the Image source,
 * Returns a new struct Image containing the result, or NULL on error. */
struct Image *apply_MEDIAN(const struct Image *source)
{
    //pointer at a pixel changes colour value, to median of the 4 adjacent pixels, above/below/right/left
    //excluding nonexistent pixels, when at edges

    if (source == NULL) {
        fprintf(stderr, "source Image given to Median is NULL");
        return NULL;
    }
    //copies source Image and assign img_median pointer to the new Image
    struct Image *img_median = copy_image(source);
    if (img_median == NULL) {
        fprintf(stderr, "img_median failed to load from copy_image");
        return NULL;
    }

    //initializes a simple int pixel tracker for pixel operated on
    int pixel;
        //for every row
        for (int h = 0; h < source->height; h++) {
            //sets boolean value to true if at height start/end if pixel at edge
            bool hs, he = false;
            if (h == 0) {
                hs = true;
            } else if (h == (source->height - 1)) {
                he = true;
            }

            //for every column
            for (int w = 0; w < source->width; w++) {
                //sets boolean value to true if at width start/end if pixel at edge
                bool ws, we = false;
                if (w == 0)  {
                    ws = true;
                } else if (w == (source->width - 1)) {
                    we = true;
                }

                //updates pixel tracket to current pixel being operated on
                pixel = (w) + (h * source->width);

                //starting at 4 for adjacent pixels (0th value being target pixel)
                //decrements for each out of bounds adjacent pixel
                int arrSize = 4;
                if (hs) arrSize--;
                if (he) arrSize--;
                if (ws) arrSize--;
                if (we) arrSize--;
                //creates arrays for pixel rgb value to take median
                int red[arrSize];
                int green[arrSize];
                int blue[arrSize];
        
                //c tracks the number of pixels in the scope of the current operation
                int c = 0;
                //assigns rgb values to corresponding arrays
                red[0] = source->pixelArray[pixel].red;
                green[0] = source->pixelArray[pixel].green;
                blue[0] = source->pixelArray[pixel].blue;
                c++;

                    //only assigns non-outOfBounds pixel data
                    if (!hs) {
                        red[c] = source->pixelArray[pixel - source->width].red;
                        green[c] = source->pixelArray[pixel - source->width].green;
                        blue[c] = source->pixelArray[pixel - source->width].blue;
                        c++;
                    }
                    if (!he) {
                        red[c] = source->pixelArray[pixel + source->width].red;
                        green[c] = source->pixelArray[pixel + source->width].green;
                        blue[c] = source->pixelArray[pixel + source->width].blue;
                        c++;
                    }
                    if (!ws) {
                        red[c] = source->pixelArray[pixel - 1].red;
                        green[c] = source->pixelArray[pixel - 1].green;
                        blue[c] = source->pixelArray[pixel - 1].blue;
                        c++;
                    }
                    if (!we) {
                        red[c] = source->pixelArray[pixel + 1].red;
                        green[c] = source->pixelArray[pixel + 1].green;
                        blue[c] = source->pixelArray[pixel + 1].blue;
                        c++;
                    }

                //sorts the arrays
                qsort(red, c, sizeof(int), compare);
                qsort(green, c, sizeof(int), compare);
                qsort(blue, c, sizeof(int), compare);

                //calculates median values of the sorted arrays
                int redMedian, blueMedian, greenMedian = 0;
                if (c % 2 != 0) {
                    redMedian = red[c / 2];
                    greenMedian = green[c / 2];
                    blueMedian = blue[c / 2];
                } else {
                    redMedian = (red[(c - 1) / 2] + red[c / 2]) / 2.0;
                    greenMedian = (green[(c - 1) / 2] + green[c / 2]) / 2.0;
                    blueMedian = (blue[(c - 1) / 2] + blue[c / 2]) / 2.0;
                }

                //assigns median values img_median
                img_median->pixelArray[pixel].red = redMedian;
                img_median->pixelArray[pixel].green = greenMedian;
                img_median->pixelArray[pixel].blue = blueMedian;

            }
        }

    //successful median
    return img_median;
}

/* Perform your second task.
 * Normalizes all
 * Returns true on success, or false on error. */
bool apply_NORM(struct Image *source)
{
    if(source == NULL) {
        fprintf(stderr, "source given to NORM is NULL");
        return false;
    }

    //initializes min&max as max&min rgb values to force updating upon operation
    int min = 255;
    int max = 0;

    //for every pixel compare and update min&max
    for (int i = 0; i < source->width*source->height; i++) {
        if (source->pixelArray[i].red < min){
            min = source->pixelArray[i].red;
        } else if (source->pixelArray[i].red > max){
            max = source->pixelArray[i].red;
        }

        if (source->pixelArray[i].green < min){
            min = source->pixelArray[i].green;
        } else if (source->pixelArray[i].green > max){
            max = source->pixelArray[i].green;
        }

        if (source->pixelArray[i].blue < min){
            min = source->pixelArray[i].blue;
        } else if (source->pixelArray[i].blue > max){
            max = source->pixelArray[i].blue;
        }
    }    

    //values for calculating NORM
    int offset = min;
    float scaling_factor = 1;
    if (max-min != 0) {
        scaling_factor = (float)255 / (max-min);
    }

    //updates rgb values of each pixel to NORMed value
    for (int i = 0; i < (source->width*source->height); i++) {
        source->pixelArray[i].red = (unsigned char)((source->pixelArray[i].red - offset) * scaling_factor);
        source->pixelArray[i].green = (unsigned char)((source->pixelArray[i].green - offset) * scaling_factor);
        source->pixelArray[i].blue = (unsigned char)((source->pixelArray[i].blue - offset) * scaling_factor);

        //handles overflow
        if (source->pixelArray[i].red < 0 || source->pixelArray[i].red > 255 ||
            source->pixelArray[i].green < 0 || source->pixelArray[i].green > 255 ||
            source->pixelArray[i].blue < 0 || source->pixelArray[i].blue > 255) {
            fprintf(stderr, "NORM operation assigns overflow value");
            return false;
        }
    }    


    return true;
}

int main(int argc, char *argv[])
{

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
