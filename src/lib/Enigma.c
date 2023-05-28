#include "Enigma.h"
#include "EnigmaImpl.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

#include "stdio.h"

//#define DEBUG

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

        for (size_t i = 0; i < num_rotors; i++)
        {
            enigma->rotors[i] = new_Rotor(rotors[i], inits[i], rings[i]);
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

    size_t i = 0;
    char *ret;
    // for each character of message, put through Enigma machine
    while (ciphertext[i])
    {
        #ifdef DEBUG
        printf("\nCharacter #%lu:\n", i + 1);
        #endif

        // ignore spaces; ASCII <Space> is decimal 32
        if (ciphertext[i] != 32)
        {
            tick_Enigma(self);
        }

        // apply plugboard
        if (self->plugboard != NULL)
        {
            #ifdef DEBUG
            printf("Plugboard:\t%c -> ", ciphertext[i]);
            #endif
            ret = apply_Plugboard(self->plugboard, &ciphertext[i]);
            #ifdef DEBUG
            printf("%c\n", *ret);
            #endif
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in plugboard application.\n");
                return 0;
            }
        }

        // apply rotors first to last
        if (self->rotors != NULL)
        {
            #ifdef DEBUG
            printf("Rotors:\t\t%c -> ", ciphertext[i]);
            #endif
            ret = apply_Rotors_frwd(self->rotors, self->num_rotors, &ciphertext[i]);
            #ifdef DEBUG
            printf("%c\n", *ret);
            #endif
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in forward rotors application.\n");
                return 0;
            }
        }

        // apply reflector
        if (self->reflector != NULL)
        {
            #ifdef DEBUG
            printf("Reflector:\t%c -> ", ciphertext[i]);
            #endif
            ret = apply_Reflector(self->reflector, &ciphertext[i]);
            #ifdef DEBUG
            printf("%c\n", *ret);
            #endif
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in reflector application.\n");
                return 0;
            }
        }

        // apply rotors last to first
        if (self->rotors != NULL)
        {
            #ifdef DEBUG
            printf("Rotors:\t\t%c -> ", ciphertext[i]);
            #endif
            ret = apply_Rotors_bkwd(self->rotors, self->num_rotors, &ciphertext[i]);
            #ifdef DEBUG
            printf("%c\n", *ret);
            #endif
            if (ret == NULL)
            {
                fprintf(stderr, "Error: Failure in forward rotors application.\n");
                return 0;
            }
        }

        // apply plugboard again
        if (self->plugboard != NULL)
        {
            #ifdef DEBUG
            printf("Plugboard:\t%c -> ", ciphertext[i]);
            #endif
            ret = apply_Plugboard(self->plugboard, &ciphertext[i]);
            #ifdef DEBUG
            printf("%c\n", *ret);
            #endif
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
    for (size_t i = 0; i < self->num_rotors; i++)
    {
        self->rotors[i]->offset = new_setting[i];
    }
}

void free_Enigma(Enigma *self)
{
    if (self)
    {
        if (self->rotors)
        {
            for (size_t i = 0; i < self->num_rotors; i++) free_Rotor(self->rotors[i]);
        }
        if (self->plugboard) free_Plugboard(self->plugboard);
        if (self->reflector) free_Reflector(self->reflector);
        free(self);
    }
}

void get_setting_Enigma(Enigma *self, char *ret)
{
    // place letter representation of offsets of rotors in ret
    for (size_t i = 0; i < self->num_rotors; i++)
    {
        ret[i] = LETTERS[self->rotors[i]->offset];
    }
}

void tick_Enigma(Enigma *self)
{
    // NOTE: "double stepping": whenever a rotor is in a notch position, it turns itself
    // AND it turns the next rotor (except for last rotor by mechanical reasons; no pawl
    // for last rotor's notches)

    #ifdef DEBUG
    printf("ticks: ");
    #endif

    // determine tick for each rotor
    int carry = 1;      // always tick first rotor
    for (size_t i = 0; i < self->num_rotors; i++)
    {
        int prevOffset = self->rotors[i]->offset;
        int haveTicked = 0;

        // move rotor if carry
        if (carry)
        {
            self->rotors[i]->offset = (self->rotors[i]->offset < 25) ? ++self->rotors[i]->offset : 0;
            haveTicked = 1;
        }

        #ifdef DEBUG
        printf("%d: %c, ", carry, LETTERS[self->rotors[i]->offset]);
        #endif

        // determine if rotor's tick should cause next rotor to tick (last rotor ignored)
        int j = 27;     // start past comma in rotor's config
        carry = 0;      // tick determinant for next rotor
        while ((i != self->num_rotors - 1) && self->rotors[i]->rotorConfig[j])
        {
            /// "purpose of ring is changing the input/output without affecting notch location"
            /// "init rotates it forwards like normal, which also moves the notch"
            if (LETTERS[prevOffset] == self->rotors[i]->rotorConfig[j])
            {
                // handle double stepping
                if ((i != 0) && !haveTicked)
                {
                    #ifdef DEBUG
                    printf("Double step occuring...\n");
                    #endif

                    self->rotors[i]->offset = (self->rotors[i]->offset < 25) ? ++self->rotors[i]->offset : 0;
                }

                carry = 1;  // notch was present during tick; carry info to next rotor
                break;      // determined if notch, done with while
            }
            j++;
        }
    }

    #ifdef DEBUG
    printf("\n");
    #endif
}

void tick_n_Enigma(Enigma *self, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        tick_Enigma(self);
    }
}
