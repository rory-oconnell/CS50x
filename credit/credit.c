#include <cs50.h>
#include <stdio.h>

// Function prototype declarations
long long get_number(void);
int count_digits(long long number);
int Luhn_Algo(long long number);
int card_type(int digits, int checksum, long long number);

int main(void)
{
    // Ask for the CC number
    long long number = get_number();

    // Find number of digits on the CC
    int digits = count_digits(number);

    // Validates the checksum algorithim
    int checksum = Luhn_Algo(number);

    // Determines what type of card was input
    int n = card_type(digits, checksum, number);
    if (n == 1)
    {
        printf("INVALID\n");
    }
    else if (n == 2)
    {
        printf("AMEX\n");
    }
    else if (n == 3)
    {
        printf("MASTERCARD\n");
    }
    else if (n == 4)
    {
        printf("VISA\n");
    }

}

//Function definitions

// Function that obtains the input credit card number
long long get_number(void)
{
    long long n;
    do
    {
        n = get_long_long("Please enter your credit card number: ");
    }

    while (n < 0);
    return n;
}

// Function that counts the number of digits in the credit card
int count_digits(long long number)
{
    int length = 0;

    while (number > 0)

    {

        number = number / 10;
        length++;
    }
    return length;
}

// Function that validates the Luhn's algorithim
int Luhn_Algo(long long number)
{
    // The length of the card number
    int length = 0;

    // Returns 0 as 1 depending on whether the checksum passed or not
    int checksum = 0;

    // These are the numbers that end up getting multiplied by 2
    int blues = 0;

    // These are the numbers that are just added to the blues
    int yellows = 0;

    // variable used to handle the multiplied numbers
    int product = 0;

    while (number > 0)

    {
        if (length % 2 != 0)        // generates an alternating binary sequence depending on whether the number is even or odd
        {
            product = (number % 10) * 2;
            if (product > 9)
            {
                blues = blues + (product % 10);
                product = product / 10;
            }
            blues = blues + product;
        }
        else if (length % 2 == 0)
        {
            yellows = yellows + (number % 10);
        }

        number = number / 10;
        length++;
    }
    checksum = (blues + yellows) % 10;

    return checksum;
}

// Function that checks the various parameters of different credit cards
int card_type(int digits, int checksum, long long number)
{
    int i = 0;
    int length = 0;
    int first_digit = 0;
    int AMEX_digits = 0;
    int MC_digits = 0;

    while (number > 0)

    {
        if (length == 13)   // obtains the first two digits of a 15 digit AMEX
        {
            AMEX_digits = number % 100;
        }
        if (length == 14) // obtains the first two digits of a 16 digit MC
        {
            MC_digits = number % 100;
        }
        first_digit = number % 10; // obtains the first digit of any card
        number = number / 10;
        length++;
    }

    if (checksum != 0)  // if the card does not pass checksum, return a 1
    {
        return 1;
    }
    else if (digits == 15  && (AMEX_digits == 34 || AMEX_digits == 37))     //first number AMEX conditions
    {
        return 2;
    }
    else if (digits == 13)
    {
        return 4;
    }
    else if (digits == 16)
    {
        if (MC_digits == 51 || MC_digits == 52 || MC_digits == 53 || MC_digits == 54 || MC_digits == 55)     //first number MC conditions
        {
            return 3;
        }
        else if (first_digit == 4)
        {
            return 4;
        }
    }
    return 1;
}