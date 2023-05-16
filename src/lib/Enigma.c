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
    if ((num_rotors == 0) &&
        (rotors == NULL) &&
        (rings == NULL) &&
        (inits == NULL) &&
        (reflector == NULL) &&
        (num_pairs == 0) &&
        (pairs == NULL))
    {
        fprintf(stderr, "Error: No valid arguments passed to `new_Enigma`.\n");
        return 0;
    }

    //Enigma *enigma = NEW_TYPE(Enigma);
    Enigma *enigma = (Enigma*)malloc(sizeof(Enigma));
    if (!enigma)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    // start all as null
    enigma->plugboard = NULL;
    enigma->reflector = NULL;

    if ((num_pairs != 0) && (pairs != NULL))
    {
        enigma->plugboard = new_Plugboard(num_pairs, pairs);
        if (!enigma->plugboard)
        {
            fprintf(stderr, "Error: Failure in plugboard creation.\n");
            return 0;
        }
    }

    if (reflector != NULL)
    {
        enigma->reflector = new_Reflector(reflector);
        if (!enigma->reflector)
        {
            fprintf(stderr, "Error: Failure in reflector creation.\n");
            return 0;
        }
    }

    // NOTICE: `enigma` must be freed with `free_Enigma` after use
    return enigma;
}

char *encrypt_Enigma(Enigma *self, char *dst, const char *src)
{
    char *message_PB1 = NULL,
         *message_Rfl = NULL,
         *message_PB2 = NULL;

    // apply plugboard
    if (self->plugboard != NULL)
    {
        message_PB1 = apply_Plugboard(self->plugboard, src);
        if (message_PB1 == NULL)
        {
            fprintf(stderr, "Error: Failure in plugboard application.\n");
            return 0;
        }
    }
    // apply reflector
    if (self->reflector != NULL)
    {
        message_Rfl = (self->plugboard != NULL) ? apply_Reflector(self->reflector, message_PB1)
                                                : apply_Reflector(self->reflector, src);
        if (message_Rfl == NULL)
        {
            fprintf(stderr, "Error: Failure in reflector application.\n");
            return 0;
        }
    }
    // apply plugboard again
    if (self->plugboard != NULL)
    {
        message_PB2 = (self->reflector != NULL) ? apply_Plugboard(self->plugboard, message_Rfl)
                                                : apply_Plugboard(self->plugboard, message_PB1);
        if (message_PB2 == NULL)
        {
            fprintf(stderr, "Error: Failure in plugboard application.\n");
            return 0;
        }
    }

    // copy result to dst
    if (message_PB2 != NULL)        strcpy(dst, message_PB2);
    else if (message_Rfl != NULL)   strcpy(dst, message_Rfl);

    // cleanup
    if (self->plugboard != NULL)
    {
        free(message_PB1);
        free(message_PB2);
    }
    if (self->reflector != NULL) free(message_Rfl);

    return dst;
}

void reset_rotor_Enigma(Enigma *self, size_t *new_setting){}

void free_Enigma(Enigma *self)
{
    if (self->plugboard) free_Plugboard(self->plugboard);
    if (self->reflector) free_Reflector(self->reflector);
    if (self) free(self);
}

void get_setting_Enigma(Enigma *self, char *ret){}

void tick_Enigma(Enigma *self){}

void tick_n_Enigma(Enigma *self, size_t n){}