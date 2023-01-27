#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Function prototype declarations

int rotate(int key, char* plaintext_input);

// Main function

int main(int argc, char* argv[])

{
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Get the key and validate that the key is only of numeric input

    int key = atoi(argv[1]);
    char* string_key = argv[1];
    int n = strlen(string_key);

    //printf("The string key is %s\n", string_key);

    for (int i = 0; i < n; i++)
    {
        //printf("%c is a string element of the string key\n", string_key[i]);
        //printf("%i is the ASCII value of that element\n\n", (int) string_key[i]);

        if (string_key[i] < 48 || string_key[i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //printf("The integer key is %i is valid\n\n", key);

    // Get the plaintext input from the user

    char* plaintext_input = get_string("plaintext: ");
    //printf("The plaintext input was: %s\n", plaintext_input);
    int cipher = rotate(key, plaintext_input);

}

// Function definitions

int rotate(int key, char* plaintext_input)
{

    int n = strlen(plaintext_input);

    for (int i = 0; i < n; i++)
    {
        isupper(plaintext_input[i]);
        islower(plaintext_input[i]);
        isalpha(plaintext_input[i]);

        if (isupper(plaintext_input[i]))
        {
            plaintext_input[i] = plaintext_input[i] - 65;
            plaintext_input[i] = (plaintext_input[i] + key) % 26;
            plaintext_input[i] = plaintext_input[i] + 65;
            //printf("%c is a capital letter\n", plaintext_input[i]);
        }
        else if (islower(plaintext_input[i]))
        {
            plaintext_input[i] = plaintext_input[i] - 97;
            plaintext_input[i] = (plaintext_input[i] + key) % 26;
            plaintext_input[i] = plaintext_input[i] + 97;

        }
        else if (isalpha(plaintext_input[i]) != 1)
        {
            //printf("%c is not a letter\n", plaintext_input[i]);
        }
    }
    printf("ciphertext: %s\n", plaintext_input);
    return 1;
}