#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Function prototype declarations
double Coleman_Liau(string text);

int main(void)
{
    string text = get_string("Text: ");
    int n = strlen(text);
    double reading_level = Coleman_Liau(text);
    if (reading_level > 1 && reading_level < 16)
    {
        printf("Grade %i\n", (int) reading_level);
    }
    else if (reading_level <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (reading_level >= 16)
    {
        printf("Grade 16+\n");
    }

}

//Function definitions
double Coleman_Liau(string text)
{
    double CL = 0;
    int letter_count = 0;
    int word_count = 1;         // Initialise at 1 to account for n+1 words
    int sentence_count = 0;
    int n = strlen(text);       // Establish length of characters
    double L = 0;               // Avg number of letters per 100 words
    double S = 0;               // Avg number of sentences per 100 words

    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))           // Deal with letters
        {
            letter_count++;
        }
        else if (isalpha(text[i]) != 1 && text[i] == 32)            // Deal with words

        {
            word_count++;
        }
        else if (isalpha(text[i]) != 1 && (text[i] == 46 || text[i] == 33 || text[i] == 63))        // Deal with sentences
        {
            sentence_count++;
        }
    }
    L = (((float) letter_count / (float) word_count) * 100);
    S = (((float) sentence_count / (float) word_count) * 100);
    CL = 0.0588 * L - 0.296 * S - 15.8;
    CL = (int) round(CL);
    return CL;
}