#include "Reflector.h"
#include "common.h"
#include "stdlib.h"
#include "string.h"

#include "stdio.h"

/* Your code to implement Reflector here */

Reflector *new_Reflector(const char *reflections)
{
    if (!reflections) return NULL;

    Reflector *reflector = (Reflector*)malloc(sizeof(Reflector));
    if (!reflector)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    reflector->reflections = (char*)malloc(sizeof(char) * strlen(reflections));
    if (!reflector->reflections)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    strcpy(reflector->reflections, reflections);

    // NOTICE: `reflector` must be freed after use
    return reflector;
}

char *apply_Reflector(Reflector *self, const char *message)
{
    if (!self) return NULL;
    if (!message) return NULL;

    // we can trust reflector's contents will be A-Z jumbled (or not)
    size_t messageCapacity = (sizeof(char) * strlen(message)) + 1;
    char *reflected_m = (char*)malloc(messageCapacity);
    if (!reflected_m)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    memset(reflected_m, 0, messageCapacity);

    // reflect letters of message
    int i = 0, alphaoffset;
    while (message[i])
    {
        // ignore spaces; ASCII <Space> is decimal 32
        if (message[i] == 32)
        {
            reflected_m[i] = 32;
        }
        else
        {
            // determine letter's offset from A
            alphaoffset = message[i] - 65;
            // make reflected output the reflection of this letter
            reflected_m[i] = self->reflections[alphaoffset];
        }
        i++;
    }

    // NOTICE: `reflected_m` must be freed after use
    return reflected_m;
}

void free_Reflector(Reflector *self)
{
    if (self->reflections) free(self->reflections);
    if (self) free(self);
}