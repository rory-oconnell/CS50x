#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;
char filename[100];

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //TODO: Open memory card
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    //TODO: create buffer, which will be an array of bytes.
    //Store blocks of 512 BYTES into an array
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];

    //Track number of images that were generated
    int count_image = 0;

    FILE *output_file = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input_file) == BLOCK_SIZE)
    {
        //TODO: Look for the beginning of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //write the jpeg filename
            sprintf(filename, "%03i.jpg", count_image);

            // open the output file for writing
            output_file = fopen(filename, "w");

            //Count images
            count_image++;
        }

        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}