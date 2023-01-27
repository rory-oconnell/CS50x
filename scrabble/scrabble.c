#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Captial letters range from 65 - 90
// Lowercase letters range from 97 - 122

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}


int compute_score(string word)
{
    int i;
    int j;
    int score = 0;
    int n = strlen(word);

    for (i = 0; i < n; i++)
    {
        if (islower(word[i]))
        {
            j = word[i] - 97;
        }
        else
        {
            j = word[i] - 65;
        }
        score = score + POINTS[j];
    }
    return score;
}