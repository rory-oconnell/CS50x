#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE holder;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width / 2; j++)
        {
            holder = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = holder;
        }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //As we are changing the RGB values of the image, we need to have a copy of the image in order to reference what the original RGB values were.
    RGBTRIPLE blurArray[height][width];

    //Copying an array by using the = operator doesn't work. As such I just fill the array with two for loops, referencing the original image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurArray[i][j] = image[i][j];
        }
    }

    // eight edge cases that need to be addressed.
    // corners - top left (0,0), top right (0, width), bottom left (height, 0), bottom right (height, width)
    // sides - top side (0, n), bottom side (height, n), left side (n, 0), right side (n, width).


    //we begin with a nested for loop which will allow us to iterate across rows and columns
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top left corner; taking the average of the four pixels that make up the top left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((blurArray[i][j].rgbtRed + blurArray[i][j + 1].rgbtRed + blurArray[i + 1][j + 1].rgbtRed + blurArray[i +
                                             1][j].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((blurArray[i][j].rgbtGreen + blurArray[i][j + 1].rgbtGreen + blurArray[i + 1][j + 1].rgbtGreen +
                                               blurArray[i + 1][j].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((blurArray[i][j].rgbtBlue + blurArray[i][j + 1].rgbtBlue + blurArray[i + 1][j + 1].rgbtBlue +
                                              blurArray[i + 1][j].rgbtBlue) / 4.0);
            }

            //top right corner; taking the average of the four pixels that make up the top right corner
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((blurArray[i][j].rgbtRed + blurArray[i][j - 1].rgbtRed + blurArray[i + 1][j].rgbtRed + blurArray[i +
                                             1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((blurArray[i][j].rgbtGreen + blurArray[i][j - 1].rgbtGreen + blurArray[i + 1][j].rgbtGreen +
                                               blurArray[i + 1][j - 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((blurArray[i][j].rgbtBlue + blurArray[i][j - 1].rgbtBlue + blurArray[i + 1][j].rgbtBlue + blurArray[i +
                                              1][j - 1].rgbtBlue) / 4.0);
            }

            //bottom left corner; taking the average of the four pixels that make up the bottom left corner
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((blurArray[i][j].rgbtRed + blurArray[i - 1][j].rgbtRed + blurArray[i - 1][j + 1].rgbtRed +
                                             blurArray[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((blurArray[i][j].rgbtGreen + blurArray[i - 1][j].rgbtGreen + blurArray[i - 1][j + 1].rgbtGreen +
                                               blurArray[i][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((blurArray[i][j].rgbtBlue + blurArray[i - 1][j].rgbtBlue + blurArray[i - 1][j + 1].rgbtBlue +
                                              blurArray[i][j + 1].rgbtBlue) / 4.0);
            }

            //bottom right corner; taking the average of the four pixels that make up the bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((blurArray[i][j].rgbtRed + blurArray[i][j - 1].rgbtRed + blurArray[i - 1][j - 1].rgbtRed + blurArray[i -
                                             1][j].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((blurArray[i][j].rgbtGreen + blurArray[i][j - 1].rgbtGreen + blurArray[i - 1][j - 1].rgbtGreen +
                                               blurArray[i - 1][j].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((blurArray[i][j].rgbtBlue + blurArray[i][j - 1].rgbtBlue + blurArray[i - 1][j - 1].rgbtBlue +
                                              blurArray[i - 1][j].rgbtBlue) / 4.0);
            }

            //top side; this includes all pixels that make up the top row, less the two corner pixels which are taken care of by the corner edge cases
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((blurArray[i][j - 1].rgbtRed + blurArray[i][j].rgbtRed + blurArray[i][j + 1].rgbtRed + blurArray[i +
                                             1][j - 1].rgbtRed + blurArray[i + 1][j].rgbtRed + blurArray[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((blurArray[i][j - 1].rgbtGreen + blurArray[i][j].rgbtGreen + blurArray[i][j + 1].rgbtGreen +
                                               blurArray[i + 1][j - 1].rgbtGreen + blurArray[i + 1][j].rgbtGreen + blurArray[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((blurArray[i][j - 1].rgbtBlue + blurArray[i][j].rgbtBlue + blurArray[i][j + 1].rgbtBlue + blurArray[i +
                                              1][j - 1].rgbtBlue + blurArray[i + 1][j].rgbtBlue + blurArray[i + 1][j + 1].rgbtBlue) / 6.0);
            }

            //bottom side; this includes all pixels that make up the bottom row, less the two corner pixels which are taken care of by the corner edge cases
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round((blurArray[i][j - 1].rgbtRed + blurArray[i][j].rgbtRed + blurArray[i][j + 1].rgbtRed + blurArray[i -
                                             1][j - 1].rgbtRed + blurArray[i - 1][j].rgbtRed + blurArray[i - 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((blurArray[i][j - 1].rgbtGreen + blurArray[i][j].rgbtGreen + blurArray[i][j + 1].rgbtGreen +
                                               blurArray[i - 1][j - 1].rgbtGreen + blurArray[i - 1][j].rgbtGreen + blurArray[i - 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((blurArray[i][j - 1].rgbtBlue + blurArray[i][j].rgbtBlue + blurArray[i][j + 1].rgbtBlue + blurArray[i -
                                              1][j - 1].rgbtBlue + blurArray[i - 1][j].rgbtBlue + blurArray[i - 1][j + 1].rgbtBlue) / 6.0);
            }

            //left side; this includes all pixels that make up the left column, less the two corner pixels which are taken care of by the corner edge cases
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((blurArray[i - 1][j].rgbtRed + blurArray[i][j].rgbtRed + blurArray[i + 1][j].rgbtRed + blurArray[i -
                                             1][j + 1].rgbtRed + blurArray[i][j + 1].rgbtRed + blurArray[i + 1][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((blurArray[i - 1][j].rgbtGreen + blurArray[i][j].rgbtGreen + blurArray[i + 1][j].rgbtGreen +
                                               blurArray[i - 1][j + 1].rgbtGreen + blurArray[i][j + 1].rgbtGreen + blurArray[i + 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((blurArray[i - 1][j].rgbtBlue + blurArray[i][j].rgbtBlue + blurArray[i + 1][j].rgbtBlue + blurArray[i -
                                              1][j + 1].rgbtBlue + blurArray[i][j + 1].rgbtBlue + blurArray[i + 1][j + 1].rgbtBlue) / 6.0);
            }

            //right side; this includes all pixels that make up the left column, less the two corner pixels which are taken care of by the corner edge cases
            else if (j == width - 1)
            {
                image[i][j].rgbtRed  = round((blurArray[i - 1][j].rgbtRed + blurArray[i][j].rgbtRed + blurArray[i + 1][j].rgbtRed + blurArray[i -
                                              1][j - 1].rgbtRed + blurArray[i][j - 1].rgbtRed + blurArray[i + 1][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((blurArray[i - 1][j].rgbtGreen + blurArray[i][j].rgbtGreen + blurArray[i + 1][j].rgbtGreen +
                                               blurArray[i - 1][j - 1].rgbtGreen + blurArray[i][j - 1].rgbtGreen + blurArray[i + 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((blurArray[i - 1][j].rgbtBlue + blurArray[i][j].rgbtBlue + blurArray[i + 1][j].rgbtBlue + blurArray[i -
                                              1][j - 1].rgbtBlue + blurArray[i][j - 1].rgbtBlue + blurArray[i + 1][j - 1].rgbtBlue) / 6.0);
            }

            //this case will deal with the vast majority of the pixels in the image; those that are neither a corner nor an edge.
            else
            {
                image[i][j].rgbtRed = round((blurArray[i - 1][j - 1].rgbtRed + blurArray[i - 1][j].rgbtRed + blurArray[i - 1][j + 1].rgbtRed +
                                             blurArray[i][j - 1].rgbtRed + blurArray[i][j].rgbtRed + blurArray[i][j + 1].rgbtRed + blurArray[i + 1][j - 1].rgbtRed + blurArray[i
                                                     + 1][j].rgbtRed + blurArray[i + 1][j + 1].rgbtRed) / 9.0);
                image[i][j].rgbtGreen = round((blurArray[i - 1][j - 1].rgbtGreen + blurArray[i - 1][j].rgbtGreen + blurArray[i - 1][j + 1].rgbtGreen
                                               + blurArray[i][j - 1].rgbtGreen + blurArray[i][j].rgbtGreen + blurArray[i][j + 1].rgbtGreen + blurArray[i + 1][j - 1].rgbtGreen +
                                               blurArray[i + 1][j].rgbtGreen + blurArray[i + 1][j + 1].rgbtGreen) / 9.0);
                image[i][j].rgbtBlue = round((blurArray[i - 1][j - 1].rgbtBlue + blurArray[i - 1][j].rgbtBlue + blurArray[i - 1][j + 1].rgbtBlue +
                                              blurArray[i][j - 1].rgbtBlue + blurArray[i][j].rgbtBlue + blurArray[i][j + 1].rgbtBlue + blurArray[i + 1][j - 1].rgbtBlue +
                                              blurArray[i + 1][j].rgbtBlue + blurArray[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // We need copies of the image to perform the Gx and Gy passes.
    RGBTRIPLE GxArray[height][width];
    RGBTRIPLE GyArray[height][width];
    RGBTRIPLE imageCopy[height][width];
    int GxSquare = 0;
    int GySquare = 0;
    int GxySum = 0;
    int rval = 0;
    int gval = 0;
    int bval = 0;

    float sqrtGxy = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxArray[i][j] = image[i][j];
            GyArray[i][j] = image[i][j];
            imageCopy[i][j] = image[i][j];
        }
    }

    // Each pixel comprises of three values; R, G, B. We pass the matrix over each of the R, G, and B values. A pass generates convolution values for each channel.
    // We require two passes for each pixel, Gx and Gy.
    // TODO: fill the Gx and Gy arrays using the
    // Once the Gx and Gy matrices have been filled, we can then use the figures from those matrices in the formula to fill the image.

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top left corner
            if (i == 0 && j == 0)
            {
                GxArray[i][j].rgbtRed = round((image[i][j].rgbtRed * 0 + image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 0));
                GxArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 0));
                GxArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 0));

                GyArray[i][j].rgbtRed = round((image[i][j].rgbtRed * 0 + image[i][j + 1].rgbtRed * 0 + image[i + 1][j + 1].rgbtRed * 1 + image[i + 1][j].rgbtRed * 2));
                GyArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen * 0 + image[i][j + 1].rgbtGreen * 0 + image[i + 1][j + 1].rgbtGreen * 1 + image[i + 1][j].rgbtGreen * 2));
                GyArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue * 0 + image[i][j + 1].rgbtBlue * 0 + image[i + 1][j + 1].rgbtBlue * 1 + image[i + 1][j].rgbtBlue * 2));
            }

            //top right corner
            else if (i == 0 && j == width - 1)
            {
                GxArray[i][j].rgbtRed = round((image[i][j].rgbtRed*0 + image[i][j - 1].rgbtRed*-2 + image[i + 1][j].rgbtRed*0 + image[i + 1][j - 1].rgbtRed*-1));
                GxArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen*0 + image[i][j - 1].rgbtGreen*-2 + image[i + 1][j].rgbtGreen*0 + image[i + 1][j - 1].rgbtGreen*-1));
                GxArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue*0 + image[i][j - 1].rgbtBlue*-2 + image[i + 1][j].rgbtBlue*0 + image[i + 1][j - 1].rgbtBlue*-1));

                GyArray[i][j].rgbtRed = round((image[i][j].rgbtRed*0 + image[i][j - 1].rgbtRed*0 + image[i + 1][j].rgbtRed*2 + image[i + 1][j - 1].rgbtRed*1));
                GyArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen*0 + image[i][j - 1].rgbtGreen*0 + image[i + 1][j].rgbtGreen*2 + image[i + 1][j - 1].rgbtGreen*1));
                GyArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue*0 + image[i][j - 1].rgbtBlue*0 + image[i + 1][j].rgbtBlue*2 + image[i + 1][j - 1].rgbtBlue*1));
            }

            //bottom left corner
            else if (i == height - 1 && j == 0)
            {
                GxArray[i][j].rgbtRed = round((image[i][j].rgbtRed*0 + image[i - 1][j].rgbtRed*0 + image[i - 1][j + 1].rgbtRed*1 + image[i][j + 1].rgbtRed*2));
                GxArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen*0 + image[i - 1][j].rgbtGreen*0 + image[i - 1][j + 1].rgbtGreen*1 + image[i][j + 1].rgbtGreen*2));
                GxArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue*0 + image[i - 1][j].rgbtBlue*0 + image[i - 1][j + 1].rgbtBlue*1 + image[i][j + 1].rgbtBlue*2));

                GyArray[i][j].rgbtRed = round((image[i][j].rgbtRed*0 + image[i - 1][j].rgbtRed*-2 + image[i - 1][j + 1].rgbtRed*-1 + image[i][j + 1].rgbtRed*0));
                GyArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen*0 + image[i - 1][j].rgbtGreen*-2 + image[i - 1][j + 1].rgbtGreen*-1 + image[i][j + 1].rgbtGreen*0));
                GyArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue*0 + image[i - 1][j].rgbtBlue*-2 + image[i - 1][j + 1].rgbtBlue*-1 + image[i][j + 1].rgbtBlue*0));
            }

            //bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                GxArray[i][j].rgbtRed = round((image[i][j].rgbtRed*0 + image[i][j - 1].rgbtRed*-2 + image[i - 1][j - 1].rgbtRed*-1 + image[i - 1][j].rgbtRed*0));
                GxArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen*0 + image[i][j - 1].rgbtGreen*-2 + image[i - 1][j - 1].rgbtGreen*-1 + image[i - 1][j].rgbtGreen*0));
                GxArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue*0 + image[i][j - 1].rgbtBlue*-2 + image[i - 1][j - 1].rgbtBlue*-1 + image[i - 1][j].rgbtBlue*0));

                GyArray[i][j].rgbtRed = round((image[i][j].rgbtRed*0 + image[i][j - 1].rgbtRed*0 + image[i - 1][j - 1].rgbtRed*-1 + image[i - 1][j].rgbtRed*-2));
                GyArray[i][j].rgbtGreen = round((image[i][j].rgbtGreen*0 + image[i][j - 1].rgbtGreen*0 + image[i - 1][j - 1].rgbtGreen*-1 + image[i - 1][j].rgbtGreen*-2));
                GyArray[i][j].rgbtBlue = round((image[i][j].rgbtBlue*0 + image[i][j - 1].rgbtBlue*0 + image[i - 1][j - 1].rgbtBlue*-1 + image[i - 1][j].rgbtBlue*-2));
            }

            //top side; this includes all pixels that make up the top row, less the two corner pixels which are taken care of by the corner edge cases
            else if (i == 0)
            {
                GxArray[i][j].rgbtRed = round((image[i][j - 1].rgbtRed*-2 + image[i][j].rgbtRed*0 + image[i][j + 1].rgbtRed*2 + image[i + 1][j - 1].rgbtRed*-1 + image[i + 1][j].rgbtRed*0 + image[i + 1][j + 1].rgbtRed*1));
                GxArray[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen*-2 + image[i][j].rgbtGreen*0 + image[i][j + 1].rgbtGreen*2 + image[i + 1][j - 1].rgbtGreen*-1 + image[i + 1][j].rgbtGreen*0 + image[i + 1][j + 1].rgbtGreen*1));
                GxArray[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue*-2 + image[i][j].rgbtBlue*0 + image[i][j + 1].rgbtBlue*2 + image[i + 1][j - 1].rgbtBlue*-1 + image[i + 1][j].rgbtBlue*0 + image[i + 1][j + 1].rgbtBlue*1));

                GyArray[i][j].rgbtRed = round((image[i][j - 1].rgbtRed*0 + image[i][j].rgbtRed*0 + image[i][j + 1].rgbtRed*0 + image[i + 1][j - 1].rgbtRed*1 + image[i + 1][j].rgbtRed*2 + image[i + 1][j + 1].rgbtRed*1));
                GyArray[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen*0 + image[i][j].rgbtGreen*0 + image[i][j + 1].rgbtGreen*0 + image[i + 1][j - 1].rgbtGreen*1 + image[i + 1][j].rgbtGreen*2 + image[i + 1][j + 1].rgbtGreen*1));
                GyArray[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue*0 + image[i][j].rgbtBlue*0 + image[i][j + 1].rgbtBlue*0 + image[i + 1][j - 1].rgbtBlue*1 + image[i + 1][j].rgbtBlue*2 + image[i + 1][j + 1].rgbtBlue*1));
            }

            //bottom side; this includes all pixels that make up the bottom row, less the two corner pixels which are taken care of by the corner edge cases
            else if (i == height - 1)
            {
                GxArray[i][j].rgbtRed = round((image[i][j - 1].rgbtRed*-2 + image[i][j].rgbtRed*0 + image[i][j + 1].rgbtRed*2 + image[i - 1][j - 1].rgbtRed*-1 + image[i - 1][j].rgbtRed*0 + image[i - 1][j + 1].rgbtRed*1));
                GxArray[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen*-2 + image[i][j].rgbtGreen*0 + image[i][j + 1].rgbtGreen*2 + image[i - 1][j - 1].rgbtGreen*-1 + image[i - 1][j].rgbtGreen*0 + image[i - 1][j + 1].rgbtGreen*1));
                GxArray[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue*-2 + image[i][j].rgbtBlue*0 + image[i][j + 1].rgbtBlue*2 + image[i - 1][j - 1].rgbtBlue*-1 + image[i - 1][j].rgbtBlue*0 + image[i - 1][j + 1].rgbtBlue*1));

                GyArray[i][j].rgbtRed = round((image[i][j - 1].rgbtRed*0 + image[i][j].rgbtRed*0 + image[i][j + 1].rgbtRed*0 + image[i - 1][j - 1].rgbtRed*-1 + image[i - 1][j].rgbtRed*-2 + image[i - 1][j + 1].rgbtRed*-1));
                GyArray[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen*0 + image[i][j].rgbtGreen*0 + image[i][j + 1].rgbtGreen*0 + image[i - 1][j - 1].rgbtGreen*-1 + image[i - 1][j].rgbtGreen*-2 + image[i - 1][j + 1].rgbtGreen*-1));
                GyArray[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue*0 + image[i][j].rgbtBlue*0 + image[i][j + 1].rgbtBlue*0 + image[i - 1][j - 1].rgbtBlue*-1 + image[i - 1][j].rgbtBlue*-2 + image[i - 1][j + 1].rgbtBlue*-1));
            }

            //left side; this includes all pixels that make up the left column, less the two corner pixels which are taken care of by the corner edge cases
            else if (j == 0)
            {
                GxArray[i][j].rgbtRed = round((image[i - 1][j].rgbtRed*0 + image[i][j].rgbtRed*0 + image[i + 1][j].rgbtRed*0 + image[i - 1][j + 1].rgbtRed*1 + image[i][j + 1].rgbtRed*2 + image[i + 1][j + 1].rgbtRed*1));
                GxArray[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen*0 + image[i][j].rgbtGreen*0 + image[i + 1][j].rgbtGreen*0 + image[i - 1][j + 1].rgbtGreen*1 + image[i][j + 1].rgbtGreen*2 + image[i + 1][j + 1].rgbtGreen*1));
                GxArray[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue*0 + image[i][j].rgbtBlue*0 + image[i + 1][j].rgbtBlue*0 + image[i - 1][j + 1].rgbtBlue*1 + image[i][j + 1].rgbtBlue*2 + image[i + 1][j + 1].rgbtBlue*1));

                GyArray[i][j].rgbtRed = round((image[i - 1][j].rgbtRed*-2 + image[i][j].rgbtRed*0 + image[i + 1][j].rgbtRed*2 + image[i - 1][j + 1].rgbtRed*-1 + image[i][j + 1].rgbtRed*0 + image[i + 1][j + 1].rgbtRed*1));
                GyArray[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen*-2 + image[i][j].rgbtGreen*0 + image[i + 1][j].rgbtGreen*2 + image[i - 1][j + 1].rgbtGreen*-1 + image[i][j + 1].rgbtGreen*0 + image[i + 1][j + 1].rgbtGreen*1));
                GyArray[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue*-2 + image[i][j].rgbtBlue*0 + image[i + 1][j].rgbtBlue*2 + image[i - 1][j + 1].rgbtBlue*-1 + image[i][j + 1].rgbtBlue*0 + image[i + 1][j + 1].rgbtBlue*1));
            }

            //right side; this includes all pixels that make up the left column, less the two corner pixels which are taken care of by the corner edge cases
            else if (j == width - 1)
            {
                GxArray[i][j].rgbtRed  = round((image[i - 1][j].rgbtRed*0 + image[i][j].rgbtRed*0 + image[i + 1][j].rgbtRed*0 + image[i - 1][j - 1].rgbtRed*-1 + image[i][j - 1].rgbtRed*-2 + image[i + 1][j - 1].rgbtRed*-1));
                GxArray[i][j].rgbtGreen  = round((image[i - 1][j].rgbtGreen*0 + image[i][j].rgbtGreen*0 + image[i + 1][j].rgbtGreen*0 + image[i - 1][j - 1].rgbtGreen*-1 + image[i][j - 1].rgbtGreen*-2 + image[i + 1][j - 1].rgbtGreen*-1));
                GxArray[i][j].rgbtBlue  = round((image[i - 1][j].rgbtBlue*0 + image[i][j].rgbtBlue*0 + image[i + 1][j].rgbtBlue*0 + image[i - 1][j - 1].rgbtBlue*-1 + image[i][j - 1].rgbtBlue*-2 + image[i + 1][j - 1].rgbtBlue*-1));

                GyArray[i][j].rgbtRed  = round((image[i - 1][j].rgbtRed*-1 + image[i][j].rgbtRed*0 + image[i + 1][j].rgbtRed*1 + image[i - 1][j - 1].rgbtRed*-2 + image[i][j - 1].rgbtRed*0 + image[i + 1][j - 1].rgbtRed*2));
                GyArray[i][j].rgbtGreen  = round((image[i - 1][j].rgbtGreen*-1 + image[i][j].rgbtGreen*0 + image[i + 1][j].rgbtGreen*1 + image[i - 1][j - 1].rgbtGreen*-2 + image[i][j - 1].rgbtGreen*0 + image[i + 1][j - 1].rgbtGreen*2));
                GyArray[i][j].rgbtBlue  = round((image[i - 1][j].rgbtBlue*-1 + image[i][j].rgbtBlue*0 + image[i + 1][j].rgbtBlue*1 + image[i - 1][j - 1].rgbtBlue*-2 + image[i][j - 1].rgbtBlue*0 + image[i + 1][j - 1].rgbtBlue*2));
            }

            //this case will deal with the vast majority of the pixels in the image; those that are neither a corner nor an edge.
            else
            {
                rval = round((image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1));
                if (rval > 255)
                rval = 255;
                GxArray[i][j].rgbtRed = rval;

                gval = ((image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1));
                if (gval > 255)
                gval = 255;
                GxArray[i][j].rgbtGreen = gval;

                bval = ((image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1));
                if (bval > 255)
                bval = 255;
                GxArray[i][j].rgbtBlue = bval;

                rval = ((image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1));
                if (rval > 255)
                rval = 255;
                GyArray[i][j].rgbtRed = rval;

                gval = ((image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1));
                if (gval > 255)
                gval = 255;
                GyArray[i][j].rgbtGreen = gval;

                bval = ((image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1));
                if (bval > 255)
                bval = 255;
                GyArray[i][j].rgbtBlue = bval;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = round(sqrt((GxArray[i][j].rgbtRed * GxArray[i][j].rgbtRed) + (GyArray[i][j].rgbtRed * GyArray[i][j].rgbtRed)));
            GxSquare = GxArray[i][j].rgbtRed * GxArray[i][j].rgbtRed;
            GySquare = GyArray[i][j].rgbtRed * GyArray[i][j].rgbtRed;
            GxySum = GxSquare + GySquare;
            sqrtGxy = round(sqrt(GxySum));
            if (sqrtGxy > 255)
            {
                sqrtGxy = 255;
            }
            imageCopy[i][j].rgbtRed = sqrtGxy;
            image[i][j].rgbtRed = sqrtGxy;


            image[i][j].rgbtGreen = round(sqrt((GxArray[i][j].rgbtGreen * GxArray[i][j].rgbtGreen) + (GyArray[i][j].rgbtGreen * GyArray[i][j].rgbtGreen)));
            GxSquare = GxArray[i][j].rgbtGreen * GxArray[i][j].rgbtGreen;
            GySquare = GyArray[i][j].rgbtGreen * GyArray[i][j].rgbtGreen;
            GxySum = GxSquare + GySquare;
            sqrtGxy = round(sqrt(GxySum));
            if (sqrtGxy > 255)
            {
                sqrtGxy = 255;
            }
            imageCopy[i][j].rgbtGreen = sqrtGxy;
            image[i][j].rgbtGreen = sqrtGxy;


            image[i][j].rgbtBlue = round(sqrt((GxArray[i][j].rgbtBlue * GxArray[i][j].rgbtBlue) + (GyArray[i][j].rgbtBlue * GyArray[i][j].rgbtBlue)));
            GxSquare = GxArray[i][j].rgbtBlue * GxArray[i][j].rgbtBlue;
            GySquare = GyArray[i][j].rgbtBlue * GyArray[i][j].rgbtBlue;
            GxySum = GxSquare + GySquare;
            sqrtGxy = round(sqrt(GxySum));
            if (sqrtGxy > 255)
            {
                sqrtGxy = 255;
            }
            imageCopy[i][j].rgbtBlue = sqrtGxy;
            image[i][j].rgbtBlue = sqrtGxy;
        }
    }

return;
}