#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        printf("Positive Number: ");
        scanf("%i", &n);
    }
    while (n > 8 || n < 1);

    for (int i = 1; i <= n; i++) // Acts as a global counter
    {

        for (int k = n - i; k > 0; k--) // Governs white space
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++) // Governs hashes
        {
            printf("#");
        }
        for (int m = 1; m == 1; m++) // Governs new lines
        {

            printf("\n");
        }
    }

}