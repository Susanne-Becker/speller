/**
 * Dictionary.c -> speller.c
 *
 * Implements a dictionary's functionality.
 *
 * Gemaakt door: Susanne Becker
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// define linked list node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;


const int N = 26;
node *table[N];

int wordcount = 0;

/**
* Returns integer hash value for a given a string
**/
int hash(const char *hashing)
{
    int hash = (tolower(hashing[0]) - 'a');
    return hash;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Hash the word to compare and set list to hash
    node *list = table[hash(word)];

    // check for error
    if (list == NULL)
    {
        return false;
    }

    // check until the end of the linked list
    while (list != NULL)
    {
        if (strcasecmp(list->word, word) == 0)
        {
            return true;
        }
        list = list->next;
    }
    free(list);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *file = fopen(dictionary, "r");

    // initialise word
    char word[LENGTH + 1];

    // iterate through dictionary words
    while (fscanf(file, "%s", word) != EOF)
    {
        // new node
        node *current = malloc(sizeof(node));

        // check for error
        if (current == NULL)
        {
            return false;
        }
        else
        {
            // copy word in node
            strcpy(current->word, word);

            // use hash function to determine which bucket to insert word into
            int n = hash(current->word);

            // linked list
            current->next = table[n];
            table[n] = current;
        }
        wordcount++;
    }
    // close file
    fclose(file);

    // return true if successful
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *next = table[i];
            table[i] = table[i]->next;
            free(next);
        }
    }
    return true;
}