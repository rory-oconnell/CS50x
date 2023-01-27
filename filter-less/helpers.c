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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double originalRed;
    double originalGreen;
    double originalBlue;

    double newRed;
    double newGreen;
    double newBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            newRed = round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));
            if (newRed > 255)
            {
                newRed = 255;
            }

            image[i][j].rgbtRed = newRed;
            newGreen = round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));

            if (newGreen > 255)
            {
                newGreen = 255;
            }


            image[i][j].rgbtGreen = newGreen;
            newBlue = round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));

            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image[i][j].rgbtBlue = newBlue;
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