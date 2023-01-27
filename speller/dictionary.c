// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>
#include "dictionary.h"

int wordcount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 456976;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // make a pointer variable called cursor

    int index = hash(word);
    node *cursor = table[index];

    // we have our cursor initialised to the first point in the table according to the hash function
    // we need to set up a recursive function that will traverse the words in that chain
    // most notably, we want to do this to separate out the malloc portion of check, so we aren't recursively mallocing nodes

    // Recursive traverse function goes here
    if (cursor == NULL)
    {
        return false;
    }

    while (strcasecmp(cursor->word, word) != 0)
    {
        if (strcasecmp(cursor->word, word) != 0 && cursor->next == NULL)
        {
            return false;
        }

        else if (strcasecmp(cursor->word, word) != 0)
        {
            cursor = cursor->next;
        }
    }

    if (strcasecmp(cursor->word, word) == 0)
    {
        return true;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)

{
    int key[4];
    int placement = 0;

    if (strlen(word) == 1)
    {
        key[0] = (toupper(word[0]) % 65) * 17576;
        key[1] = 0;
        key[2] = 0;
        key[3] = 0;

    }

    else if (strlen(word) == 2)
    {
        key[0] = (toupper(word[0]) % 65) * 17576;
        key[1] = (toupper(word[1]) % 65) * 676;
        key[2] = 0;
        key[3] = 0;
    }

    else if (strlen(word) == 3)
    {
        key[0] = (toupper(word[0]) % 65) * 17576;
        key[1] = (toupper(word[1]) % 65) * 676;
        key[2] = (toupper(word[1]) % 65) * 26;
        key[3] = 0;
    }

    else if (strlen(word) >= 4)
    {
        for (int i = 0; i < 4; i++)
        {
            key[i] = (toupper(word[i]) % 65);

            if (i == 0)
            {
                key[i] = key[i] * 676;
            }
            else if (i == 1)
            {
                key[i] = key[i] * 26;
            }
        }
    }

    placement = key[0] + key[1] + key[2];

    return placement;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    // use fopen, remember to check if the return value is NULL
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary.\n");
        return -1;
    }

    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node)); // malloc space for a new node
        strcpy(n->word, buffer);        // copying scanned word into malloc
        wordcount++;
        int hashnumber = hash(n->word);
        n->next = table[hash(n->word)]; // point to the word at the head position
        table[hash(n->word)] = n;       // place the new word at the head of the array (the next word was captured in the line previous)
    }

    if (fscanf(file, "%s", buffer) == EOF)
    {
        fclose(file);
        return true;
    }
    fclose(file);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N - 1; i++)
    {
        node *cursor = table[i];    // cursor initialised to the first node
        node *tmp = table[i];       // tmp initialised to the first node

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
