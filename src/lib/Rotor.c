#include "Rotor.h"
#include "common.h"

#include "string.h"
#include "stdio.h"

/* Your code to implement Rotor here */

Rotor *new_Rotor(const char *rotorConfig, size_t init, size_t ring)
{
    if (!rotorConfig) return NULL;

    Rotor *rotor = (Rotor*)malloc(sizeof(Rotor));
    if (!rotor)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }

    rotor->rotorConfig = (char*)malloc(sizeof(char) * strlen(rotorConfig) + 1);
    if (!rotor->rotorConfig)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    strcpy(rotor->rotorConfig, rotorConfig);

    rotor->offset = init;
    rotor->ringDelta = ring;

    // NOTICE: `rotor` must be freed after use
    return rotor;
}

char *apply_Rotors_frwd(Rotor **rotors, size_t num_rotors, char *letter)
{
    if (!rotors) return NULL;
    if (!letter) return NULL;

    for (size_t i = 0; i < num_rotors; i++)
    {
        // ignore spaces; ASCII <Space> is decimal 32
        if (*letter != 32)
        {
            // determine letter's entry point into rotor (Self := rotor)
            size_t alphaoffsetSelf = ((*letter - 65) + (rotors[i]->offset - rotors[i]->ringDelta));
            alphaoffsetSelf = (alphaoffsetSelf + 26) % 26;
            // output based on rotor configuration
            char outputSelf = rotors[i]->rotorConfig[alphaoffsetSelf];
            // determine which input this letter will be wrt the world (other rotors/reflector)
            size_t alphaoffsetWorld = (outputSelf - 65) - (rotors[i]->offset - rotors[i]->ringDelta);
            alphaoffsetWorld = (alphaoffsetWorld + 26) % 26;
            *letter = LETTERS[alphaoffsetWorld];
        }
    }

    return letter;
}

char *apply_Rotors_bkwd(Rotor **rotors, size_t num_rotors, char *letter)
{
    if (!rotors) return NULL;
    if (!letter) return NULL;

    for (size_t i = num_rotors; i > 0; i--)
    {
        // ignore spaces; ASCII <Space> is decimal 32
        if (*letter != 32)
        {
            // determine rotor output offset due to rotation
            size_t outOffset = ((*letter - 65) + (rotors[i - 1]->offset - rotors[i - 1]->ringDelta));
            outOffset = (outOffset + 26) % 26;
            char imgSelf = LETTERS[outOffset];
            // find letter in rotor's configuration to get rotor input
            size_t j = 0;
            while (rotors[i - 1]->rotorConfig[j] != imgSelf) j++;
            // subtract offsets to rotor configuration to get the world input
            j = j - (rotors[i - 1]->offset - rotors[i - 1]->ringDelta);
            j = (j + 26) % 26;
            // determine preimage
            *letter = LETTERS[j];
        }
    }

    return letter;
}

void free_Rotor(Rotor *self)
{
    if (self)
    {
        if (self->rotorConfig) free(self->rotorConfig);
        free(self);
    }
}
