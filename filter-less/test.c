#include <time.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define height 6
#define width 6


int line_1[6] = {2, 4, 6, 7, 3, 8};
int line_2[6] = {7, 4, 5, 1, 8, 9};
int line_3[6] = {6, 4, 1, 9, 2, 7};
int line_4[6] = {3, 4, 7, 1, 9, 8};
int line_5[6] = {3, 9, 1, 8, 6, 5};
int line_6[6] = {8, 9, 5, 3, 2, 6};

int testArray[height][width];
int blurArray[height][width];

int main(void)
{
    for (int i = 0; i < 6; i++)
    {
        testArray[0][i] = line_1[i];
        blurArray[0][i] = line_1[i];


        testArray[1][i] = line_2[i];
        blurArray[1][i] = line_2[i];


        testArray[2][i] = line_3[i];
        blurArray[2][i] = line_3[i];


        testArray[3][i] = line_4[i];
        blurArray[3][i] = line_4[i];


        testArray[4][i] = line_5[i];
        blurArray[4][i] = line_5[i];


        testArray[5][i] = line_6[i];
        blurArray[5][i] = line_6[i];

    }

    for (int i = 0; i < height; i++)
    {
        printf("\n");
        for (int j = 0; j < width; j++)
        {
            printf("%i ", testArray[i][j]);
        }
    }
        printf("\n\n");

    // eight edge cases that need to be addressed.
    // corners - top left (0,0), top right (0, width), bottom left (height, 0), bottom right (height, width)
    // sides - top side (0, n), bottom side (height, n), left side (n, 0), right side (n, width).

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)                       //top left
            blurArray[i][j] = round((testArray[i][j] + testArray[i][j + 1] + testArray[i + 1][j + 1] + testArray[i + 1][j])/4.0);

            else if (i == 0 && j == width - 1)          //top right
            blurArray[i][j] = round((testArray[i][j] + testArray[i][j - 1] + testArray[i + 1][j] + testArray[i + 1][j - 1])/4.0);

            else if (i == height - 1 && j == 0)         //bottom left
            blurArray[i][j] = round((testArray[i][j] + testArray[i - 1][j] + testArray[i - 1][j + 1] + testArray[i][j + 1])/4.0);

            else if (i == height - 1 && j == width - 1) //bottom right
            blurArray[i][j] = round((testArray[i][j] + testArray[i][j - 1] + testArray[i - 1][j - 1] + testArray[i - 1][j])/4.0);

            else if (i == 0)        //top side
            blurArray[i][j] = round((testArray[i][j - 1] + testArray[i][j] + testArray[i][j + 1] + testArray[i + 1][j - 1] + testArray[i + 1][j] + testArray[i + 1][j + 1])/6.0);

            else if (i == height - 1)       //bottom side
            blurArray[i][j] = round((testArray[i][j - 1] + testArray[i][j] + testArray[i][j + 1] + testArray[i - 1][j - 1] + testArray[i - 1][j] + testArray[i - 1][j + 1])/6.0);

            else if (j == 0)       //left side
            blurArray[i][j] = round((testArray[i - 1][j] + testArray[i][j] + testArray[i + 1][j] + testArray[i - 1][j + 1] + testArray[i][j + 1] + testArray[i + 1][j + 1])/6.0);

            else if (j == width - 1)       //right side
            blurArray[i][j] = round((testArray[i - 1][j] + testArray[i][j] + testArray[i + 1][j] + testArray[i - 1][j - 1] + testArray[i ][j - 1] + testArray[i - 1][j - 1])/6.0);

            else
            blurArray[i][j] = round((testArray[i - 1][j - 1] + testArray[i - 1][j] + testArray[i - 1][j + 1] + testArray[i][j - 1] + testArray[i][j] + testArray[i][j + 1] + testArray[i + 1][j - 1] + testArray[i + 1][j] + testArray[i + 1][j + 1])/9.0);
        }

    }
        for (int k = 0; k < height; k++)
    {
        printf("\n");
        for (int m = 0; m < width; m++)
        {
            printf("%i ", blurArray[k][m]);
        }
    }
        printf("\n\n");
}
