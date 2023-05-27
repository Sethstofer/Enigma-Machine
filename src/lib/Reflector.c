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
    reflector->reflections = (char*)malloc(sizeof(char) * strlen(reflections) + 1);
    if (!reflector->reflections)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    strcpy(reflector->reflections, reflections);

    // NOTICE: `reflector` must be freed after use
    return reflector;
}

char *apply_Reflector(Reflector *self, char *letter)
{
    if (!self) return NULL;
    if (!letter) return NULL;

    // ignore spaces; ASCII <Space> is decimal 32
    if (*letter != 32)
    {
        // determine letter's offset from A
        int alphaoffset = *letter - 65;
        // make reflected output the reflection of this letter
        *letter = self->reflections[alphaoffset];
    }

    return letter;
}

void free_Reflector(Reflector *self)
{
    if (self)
    {
        if (self->reflections) free(self->reflections);
        free(self);
    }
}
