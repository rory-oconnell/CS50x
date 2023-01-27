#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Get key
// Validate key
// Get plaintext
// Encipher
// Print ciphertext

int i = 0;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("./substitution KEY\n\n");
        return 1;
    }

    string key = argv[1];
    int n = strlen(key);

    if (n != 26)
    {
        printf("Key must contain 26 characters\n\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        if (isalpha(key[i]))
        {
            //printf("%c is a valid input\n", key[i]);
            //printf("The ASCII value is %i\n\n", key[i]);
        }
        else
        {
            printf("Key must only contain alphabetic characters\n\n");
            return 1;
        }
        for (int k = 0; k < i; k++)
        {
            if (key[i] == key[k])
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("Plaintext: ");
    int m = strlen(plaintext);

    for (i = 0; i < m; i++)
    {
        if (isupper(plaintext[i]))
        {
            //65 to 90
            //printf("%i is a valid input\n\n", plaintext[i]);
            int j = plaintext[i] - 65;  //j is now the zeroth position
            plaintext[i] = key[j];      //replacing the zeroth position with the key
            if (isupper(key[j]))
            {
                plaintext[i] = key[j];
            }
            else
            {
                plaintext[i] = key[j] - 32;
            }
        }
        else if (islower(plaintext[i]))
        {
            //97 to 122
            //printf("%i is a valid input\n\n", plaintext[i]);
            int j = plaintext[i] - 97;  //j is now the zeroth position
            plaintext[i] = key[j];      //replacing the zeroth position with the key
            if (islower(key[j]))
            {
                plaintext[i] = key[j];
            }
            else
            {
                plaintext[i] = key[j] + 32;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
}

