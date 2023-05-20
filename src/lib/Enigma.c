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
    enigma->rotors = NULL;
    enigma->num_rotors = 0;

    // create rotors
    if ((num_rotors != 0) && (rotors != NULL) && (inits != 0))
    {
        enigma->rotors = (Rotor**)malloc(sizeof(Rotor*) * num_rotors);
        if (!enigma->rotors)
        {
            fprintf(stderr, "Error: Failure in memory allocation.\n");
            return 0;
        }

        enigma->num_rotors = num_rotors;

        for (int i = 0; i < num_rotors; i++)
        {
            enigma->rotors[i] = new_Rotor(rotors[i], inits[i]);
            if (!enigma->rotors[i])
            {
                fprintf(stderr, "Error: Failure in rotor creation.\n");
                return 0;
            }
        }
    }

    // create plugboard
    if ((num_pairs != 0) && (pairs != NULL))
    {
        enigma->plugboard = new_Plugboard(num_pairs, pairs);
        if (!enigma->plugboard)
        {
            fprintf(stderr, "Error: Failure in plugboard creation.\n");
            return 0;
        }
    }

    // create reflector
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
    // store ciphertext on heap
    size_t messageCapacity = (sizeof(char) * strlen(src)) + 1;
    char *ciphertext = (char*)malloc(messageCapacity);
    if (!ciphertext)
    {
        fprintf(stderr, "Error: Failure in memory allocation.\n");
        return 0;
    }
    memset(ciphertext, 0, messageCapacity);
    // start ciphertext as plaintext
    strcpy(ciphertext, src);

    int i = 0;
    char *ret;
    // for each character of message, put through Enigma machine
    while (ciphertext[i])
    {
        // apply plugboard
        if (self->plugboard != NULL)
        {
            ret = apply_Plugboard(self->plugboard, &ciphertext[i]);
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in plugboard application.\n");
                return 0;
            }
        }

        // apply rotors first to last
        if (self->rotors != NULL)
        {
            ret = apply_Rotors_frwd(self->rotors, &ciphertext[i]);
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in forward rotors application.\n");
                return 0;
            }
        }

        // apply reflector
        if (self->reflector != NULL)
        {
            ret = apply_Reflector(self->reflector, &ciphertext[i]);
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in reflector application.\n");
                return 0;
            }
        }

        // apply rotors last to first
        if (self->rotors != NULL)
        {
            ret = apply_Rotors_bkwd(self->rotors, &ciphertext[i]);
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in forward rotors application.\n");
                return 0;
            }
        }

        // apply plugboard again
        if (self->plugboard != NULL)
        {
            ret = apply_Plugboard(self->plugboard, &ciphertext[i]);
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in plugboard application.\n");
                return 0;
            }
        }

        i++;
    }

    // copy result to dst
    strcpy(dst, ciphertext);

    // cleanup
    free(ciphertext);

    return dst;
}

void reset_rotor_Enigma(Enigma *self, size_t *new_setting)
{
    // "turn" the rotors to align with new settings
    for (int i = 0; i < self->num_rotors; i++)
    {
        self->rotors[i]->rotorOffset = new_setting[i];
    }
}

void free_Enigma(Enigma *self)
{
    if (self)
    {
        if (self->rotors)
        {
            for (int i = 0; i < self->num_rotors; i++) free_Rotor(self->rotors[i]);
        }
        if (self->plugboard) free_Plugboard(self->plugboard);
        if (self->reflector) free_Reflector(self->reflector);
        free(self);
    }
}

void get_setting_Enigma(Enigma *self, char *ret)
{
    // place letter representation of offsets of rotors in ret
    for (int i = 0; i < self->num_rotors; i++)
    {
        ret[i] = LETTERS[self->rotors[i]->rotorOffset];
    }
}

void tick_Enigma(Enigma *self)
{
    // determine tick for each rotor
    int carry = 1;      // always tick first rotor
    for (int i = 0; i < self->num_rotors; i++)
    {
        // move rotor if carry
        int prevOffset = self->rotors[i]->rotorOffset;
        if (carry)
        {
            self->rotors[i]->rotorOffset = (self->rotors[i]->rotorOffset < 25) ? ++self->rotors[i]->rotorOffset : 0;
        }

        // determine if rotor's tick should cause next rotor to tick
        int j = 27;     // start past comma in rotor's config
        carry = 0;      // tick determinant for next rotor
        while ((i != self->num_rotors - 1) && self->rotors[i]->rotorConfig[j])
        {
            if (self->rotors[i]->rotorConfig[j] == self->rotors[i]->rotorConfig[prevOffset])
            {
                carry = 1;  // notch was present during tick; carry info to next rotor
                break;      // determined if notch, done with while
            }
            j++;
        }
    }
}

void tick_n_Enigma(Enigma *self, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        tick_Enigma(self);
    }
}