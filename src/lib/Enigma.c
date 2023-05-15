#include "Enigma.h"
#include "EnigmaImpl.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

#include "stdio.h"

/* Your code to implement Enigma here */

Enigma *new_Enigma(size_t num_rotors, const char **rotors, size_t *rings,
                   size_t *inits, const char *reflector, size_t num_pairs,
                   const char *pairs)
{
    //Enigma *enigma = NEW_TYPE(Enigma);
    Enigma *enigma = (Enigma*)malloc(sizeof(Enigma));
    if (!enigma)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }

    enigma->plugboard = new_Plugboard(num_pairs, pairs);
    if (!enigma->plugboard)
    {
        fprintf(stderr, "Error: Failure in plugboard creation.\n");
        return 0;
    }

    // NOTICE: `enigma` must be freed with `free_Enigma` after use
    return enigma;
}

char *encrypt_Enigma(Enigma *self, char *dst, const char *src)
{
    char *ciphertxt = apply_Plugboard(self->plugboard, src);
    if (ciphertxt == NULL)
    {
        fprintf(stderr, "Error: Failure in plugboard application.\n");
        return 0;
    }
    strcpy(dst, ciphertxt);

    // cleanup
    free(ciphertxt);

    return dst;
}

void reset_rotor_Enigma(Enigma *self, size_t *new_setting){}

void free_Enigma(Enigma *self)
{
    free_Plugboard(self->plugboard);
    free(self);
}

void get_setting_Enigma(Enigma *self, char *ret){}

void tick_Enigma(Enigma *self){}

void tick_n_Enigma(Enigma *self, size_t n){}