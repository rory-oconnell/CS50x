#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plaintext_input = get_string("plaintext: ");
    printf("The plaintext input is: %s\n", plaintext_input);

    int n = strlen(plaintext_input);

    for (int i = 0; i < n; i++)
    {
        isupper(plaintext_input[i]);
        islower(plaintext_input[i]);
        isalpha(plaintext_input[i]);

    if (isupper(plaintext_input[i]))
    {
        //plaintext_input[i] = plaintext_input[i] - 65;
        printf("%c is a capital letter\n", plaintext_input[i]);
    }
    else if (islower(plaintext_input[i]))
    {
        //plaintext_input[i] = plaintext_input[i] - 97;
        printf("%c is a lowercase letter\n", plaintext_input[i]);

    }
    else if (isalpha(plaintext_input[i]) != 1)
    {
        printf("%c is not a letter\n", plaintext_input[i]);
    }
    }
}


    // int key = atoi(argv[1]);
    // string string_key = argv[1];
    // int n = strlen(string_key);

    // printf("The string key is %s\n", string_key);

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%c is a string element of the string key\n", string_key[i]);
    //     printf("%i is is the ASCII value of that element\n\n", (int) string_key[i]);

    //     if (string_key[i] < 48 || string_key[i] > 57)
    //     {
    //         printf("The integer key is not valid.\nUsage: ./caesar key\n");
    //         return 0;
    //     }

    // }

    // printf("The integer key is %i is valid\n", key);