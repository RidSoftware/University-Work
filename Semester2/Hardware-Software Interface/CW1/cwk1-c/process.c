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

// struct ImageList {
//     char input[];
//     char output[];
// };

/* Free a struct Image */
void free_image(struct Image *img)
{
    /* TODO: Question 2a */
    free(img);
    free(img->pixelArray);
}

/* Opens and reads an image file, returning a pointer to a new struct Image.
 * On error, prints an error message and returns NULL. */
struct Image *load_image(const char *filename)
{
    fprintf(stdout, "LOAD INITIATED\n");
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
    if (fscanf(f, "%3s", Image->file_type) != 1) {
        fprintf(stderr, "File Header couldn't be read %s\n", filename);
        fclose(f);
        return NULL;
    }
    //fprintf(stdout, "Image Type %s\n", Image->file_type);

    if (fscanf(f, "%d", &Image->width) != 1) {
        fprintf(stderr, "File Width couldn't be read %s\n", filename);
        fclose(f);
        return NULL;
    }
    //fprintf(stdout, "Image Width %d\n", Image->width);

    if (fscanf(f, "%d", &Image->height) != 1) {
        fprintf(stderr, "File Height couldn't be read %s\n", filename);
        fclose(f);
        return NULL;
    }
    //fprintf(stdout, "Image Height %d\n", Image->height);

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

    /* Close the file */
    fclose(f);

    if (Image == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }
    fprintf(stdout, "LOAD COMPLETE\n");
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
    fprintf(stdout, "SAVE INITIATED\n");
    /* TODO: Question 2c */
    //takes image structure and parses through as it writes data to a file using 
    FILE *f = fopen(filename, "wb");
    //fprintf(stdout, "file opened successfully \n");
    
    fprintf(f, "%s\n", img->file_type);
    //fprintf(stdout, "file_type written: %s \n", img->file_type);
    
    fprintf(f, "%d ", img->width);
    //fprintf(stdout, "width written: %d \n", img->width);
    
    fprintf(f, "%d\n", img->height);
    //fprintf(stdout, "height written: %d \n", img->height);
    //this is shoddily put together, must be made robust ^^^^

//  fprintf(NameOfFilePointer, "%d", myIntegerVariableName);
//  ^^^^^^^
//  optimal data writing format for non-binary/ascii data
//  as fwrite is explicitly for binary data
//  similar to fscan/fread paradigm

    //now the grunt work: writing binary data from IMAGE struct with fwrite
    
    for (int i = 0; i < (img->width * img->height); i++) {
        //fprintf(stdout, "pixel:%d - r%c g%c b%c \n", i, &img->pixelArray[i].red, &img->pixelArray[i].green, &img->pixelArray[i].blue);
        fwrite(&img->pixelArray[i].red, sizeof(unsigned char), 1, f);
        fwrite(&img->pixelArray[i].blue, sizeof(unsigned char), 1, f);
        fwrite(&img->pixelArray[i].green, sizeof(unsigned char), 1, f);
    }
    
   
//    // ATTEMPT2, uses fprintf to print decimals
//     for (int i = 0; i < (img->width * img->height); i++) {
//         if (fprintf(f, "%c", img->pixelArray[i].red) != 1 ||
//         fprintf(f, "%c", img->pixelArray[i].green) != 1 ||
//         fprintf(f, "%c", img->pixelArray[i].blue) != 1 ) {

//         fprintf(stderr, "failed to save pixel data on pixel:%d \n", i);
//         return false;
//         }
//     }

    // PIXEL DATA IS CONVERTED TO CHARACTERS OF DECIMAL INTS, THUS I NEED TO EITHER CAST THEM HERE  OR  

    fclose(f);

    //implement error returns on wites and saves
    fprintf(stdout, "SAVE COMPLETE\n");
    return true;
}

/* Allocate a new struct Image and copy an existing struct Image's contents
 * into it. On error, returns NULL. */
struct Image *copy_image(const struct Image *source)
{
    /* TODO: Question 2d */
    struct Image *img_copy = malloc(sizeof(*source));
    
    strcpy(img_copy->file_type, source->file_type);
    //fprintf(stdout, "%s \n", img_copy->file_type);
    img_copy->width = source->width;
    img_copy->height = source->height;
    //fprintf(stdout, "%d %d \n", img_copy->width, img_copy->height);

    
    //Image->pixelArray
    img_copy->pixelArray = (struct Pixel *)malloc(img_copy->width * img_copy->height * sizeof(struct Pixel));


    memcpy(img_copy->pixelArray, source->pixelArray, img_copy->width * img_copy->height * sizeof(struct Pixel));
    // for (int i = 0; i < (img_copy->width * img_copy->height); i++) {
    //     img_copy->pixelArray[i].red = source->pixelArray[i].red;
    //     //fprintf(stdout, "%c\n", img_copy->pixelArray[i].red);
    //     //fprintf(stdout, "%d\n", i);
    // }

    //fprintf(stdout, "%s\n", img_copy->file_type);

    return img_copy;
}

/* Perform your first task.
 * (TODO: Write a better comment here, and rename the function.
 * You may need to add or change arguments depending on the task.)
 * Returns a new struct Image containing the result, or NULL on error. */
struct Image *apply_MEDIAN(const struct Image *source)
{
    /* TODO: Question 3 */
    //return NULL;
    fprintf(stdout, "MEDIAN INITIATED\n");
    //pointer at a pixel changes colour value, to median of the 4 adjacent pixels, above/below/right/left
    //excluding nonexistent pixels, when at edges
    struct Image *img_median = copy_image(source);



    int pixel = 0;

        for (int h = 0; h < source->height; h++) {
            bool hs, he = false;
            if (h == 0) {
                hs = true;
            } else if (h == (source->height - 1)) {
                he = true;
            }

            for (int w = 0; w < source->width; w++) {
                bool ws, we = false;
                if (w == 0)  {
                    ws = true;
                } else if (w == (source->width - 1)) {
                    we = true;
                }

                pixel = (w) + (h * source->width);


                // fprintf(stdout, "pixel:%d, w/h:%d/%d, %u %u %u \n", pixel, w, h, p.r, p.g, p.b);
                int count = 4;
                if (hs) count--;
                if (he) count--;
                if (ws) count--;
                if (we) count--;



                        int compare(const void *a, const void *b) {
                            return (*(int *)a - *(int *)b);
                        }   


                //////////////////////////////////////////////////////////////////////////////
                int red[count];
                int green[count];
                int blue[count];
        

                int c = 0;
                red[0] = source->pixelArray[pixel].red;
                green[0] = source->pixelArray[pixel].green;
                blue[0] = source->pixelArray[pixel].blue;
                c++;

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

                qsort(red, c, sizeof(int), compare);
                qsort(green, c, sizeof(int), compare);
                qsort(blue, c, sizeof(int), compare);

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

                img_median->pixelArray[pixel].red = redMedian;
                img_median->pixelArray[pixel].green = greenMedian;
                img_median->pixelArray[pixel].blue = blueMedian;

                

            }
        }


    fprintf(stdout, "MEDIAN COMPLETE\n");
    return img_median;

}

/* Perform your second task.
 * (TODO: Write a better comment here, and rename the function.
 * You may need to add or change arguments depending on the task.)
 * Returns true on success, or false on error. */
bool apply_NORM(struct Image *source)
{
    /* TODO: Question 4 */
    fprintf(stdout, "NORM INITIATED\n");
    //scan for min and max for each colour values in the image
    //subtract the offset minimums, to 0   // to all
    //then multiply all values by a scaling factor so the max values are scaled to the max possible values
    int min = 255;
    int max = 0;

    for (int i = 0; i < source->width*source->height; i++) {
        if (source->pixelArray[i].red < min){
            min = source->pixelArray[i].red;
        }
        if (source->pixelArray[i].red > max){
            max = source->pixelArray[i].red;
        }

        if (source->pixelArray[i].green < min){
            min = source->pixelArray[i].green;
        }
        if (source->pixelArray[i].green > max){
            max = source->pixelArray[i].green;
        }

        if (source->pixelArray[i].blue < min){
            min = source->pixelArray[i].blue;
        }
        if (source->pixelArray[i].blue > max){
            max = source->pixelArray[i].blue;
        }
    }    

    int offset = min;
    float scaling_factor = (float)255 / (max-min);

    for (int i = 0; i < (source->width*source->height); i++) {
        int red = (int)((source->pixelArray[i].red - offset) * scaling_factor);
        int green = (int)((source->pixelArray[i].green - offset) * scaling_factor);
        int blue = (int)((source->pixelArray[i].blue - offset) * scaling_factor);

        // Check if the values are out of bounds
        red = red < 0 ? 0 : (red > 255 ? 255 : red);
        green = green < 0 ? 0 : (green > 255 ? 255 : green);
        blue = blue < 0 ? 0 : (blue > 255 ? 255 : blue);

        source->pixelArray[i].red = (unsigned char)red;
        source->pixelArray[i].green = (unsigned char)green;
        source->pixelArray[i].blue = (unsigned char)blue;
    }    


    for (int i = 0; i < (source->width*source->height); i++) {
        if (source->pixelArray[i].red == 0 || source->pixelArray[i].green == 0 || source->pixelArray[i].blue == 0){
            fprintf(stdout,"0 found\n");
        }
        if (source->pixelArray[i].red == 255 || source->pixelArray[i].green == 255 || source->pixelArray[i].blue == 255){
            fprintf(stdout,"255 found\n");
        }
    }
    
    fprintf(stdout, "NORM COMPLETE\n");
    return true;


}

int main(int argc, char *argv[])
{

    /* Check command-line arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: process INPUTFILE OUTPUTFILE\n");
        return 1;
    }

    //int images = (argc-1)/2;


    
    



    /* Load the input image */
    struct Image *in_img = load_image(argv[1]);
    if (in_img == NULL) {
        return 1;
    }
    save_image(in_img, "1stsave.hs8");
    // printPixelValues(in_img);

    /* Apply the first process */
    struct Image *out_img = apply_MEDIAN(in_img);
    if (out_img == NULL) {
        fprintf(stderr, "First process failed.\n");
        free_image(in_img);
        return 1;
    }
    save_image(in_img, "2ndsave.hs8");

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
