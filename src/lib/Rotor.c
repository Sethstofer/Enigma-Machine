#include "Rotor.h"
#include "common.h"
#include "string.h"

#include "stdio.h"

/* Your code to implement Rotor here */

Rotor *new_Rotor(const char *rotorConfig, size_t init)
{
    if (!rotorConfig) return NULL;
    if (!init) return NULL;

    Rotor *rotor = (Rotor*)malloc(sizeof(Rotor));
    if (!rotor)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }

    rotor->rotorConfig = (char*)malloc(sizeof(char) * strlen(rotorConfig));
    if (!rotor->rotorConfig)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    strcpy(rotor->rotorConfig, rotorConfig);

    rotor->rotorOffset = init;

    // NOTICE: `rotor` must be freed after use
    return rotor;
}

char *apply_Rotors_frwd(Rotor **rotors, char *letter)
{
    if (!rotors) return NULL;
    if (!letter) return NULL;

    // ...
}

char *apply_Rotors_bkwd(Rotor **rotors, char *letter)
{
    if (!rotors) return NULL;
    if (!letter) return NULL;

    // ...
}

void free_Rotor(Rotor *self)
{
    if (self)
    {
        if (self->rotorConfig) free(self->rotorConfig);
        free(self);
    }
}