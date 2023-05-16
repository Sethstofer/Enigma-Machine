#include "stdlib.h"
#include "Plugboard.h"
#include "common.h"

#include "stdio.h"

/* Your code to implement Plugboard here */

Plugboard *new_Plugboard(size_t num_pairs, const char *pairs)
{
    // potential lack of null terminator in pairs should (?) be handled by compiler
    int pairsLen = strlen(pairs);
    // ensure multiple of 2 length and num_pairs logically matches
    if ( !((pairsLen % 2 == 0) && (2 * num_pairs == pairsLen)) ) return NULL;
    if (num_pairs == 0) return NULL;
    if (pairs == NULL) return NULL;

    //Plugboard *plugboard = NEW_TYPE(Plugboard);
    Plugboard *plugboard = (Plugboard*)malloc(sizeof(Plugboard));
    if (!plugboard)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    plugboard->num_pairs = num_pairs;
    plugboard->pairs = (char*)malloc(sizeof(char) * 2 * num_pairs);
    if (!plugboard->pairs)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    strcpy(plugboard->pairs, pairs);

    // NOTICE: `plugboard` must be freed with `free_Plugboard` after use
    return plugboard;
}

char *apply_Plugboard(Plugboard *self, const char* message)
{
    if (!self) return NULL;
    if (!message) return NULL;

    size_t messageCapacity = (sizeof(char) * strlen(message)) + 1;
    char *plugboardtxt = (char*)malloc(messageCapacity);
    if (!plugboardtxt)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    memset(plugboardtxt, 0, messageCapacity);
    strcpy(plugboardtxt, message);

    int i = 0;
    while (plugboardtxt[i] != 0)
    {
        // check each character in `plugboardtxt` with plugboard switches
        for (int j = 0; j < (2 * self->num_pairs); j++)
        {
            if (plugboardtxt[i] == self->pairs[j])
            {
                // determine with what to switch
                plugboardtxt[i] = (j % 2 == 0) ? self->pairs[j + 1] : self->pairs[j - 1];
                // once switch letter is found, continue to next letter in message
                break;
            }
        }
        i++;
    }

    // NOTICE: `plugboardtxt` must be freed after use
    return plugboardtxt;
}

void free_Plugboard(Plugboard *self)
{
    if (self->pairs) free(self->pairs);
    if (self) free(self);
}