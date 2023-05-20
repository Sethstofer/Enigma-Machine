#ifndef ROTOR_H
#define ROTOR_H

#include "common.h"
#include "stdlib.h"

/* Your definition of Rotor */

typedef struct Rotor {
    char *rotorConfig;
    size_t rotorOffset;
} Rotor;

/// @brief Create a new rotor
/// @param rotorConfig The letter configuration of the rotor
/// @param init The set offset from start of rotorConfig
/// @return The created rotor
Rotor *new_Rotor(const char *rotorConfig, size_t init);

/// @brief Apply the rotors, first to last, on a letter
/// @param rotors The rotors to apply
/// @param letter Address of letter to go through the rotors
/// @return Address of cipher result from applying the rotors forwardly
char *apply_Rotors_frwd(Rotor **rotors, char *letter);

/// @brief Apply the rotors, last to first, on a letter after reflection
/// @param rotors The rotors to apply
/// @param letter Address of letter to go through the rotors
/// @return Address of cipher result from applying the rotors backwardly
char *apply_Rotors_bkwd(Rotor **rotors, char *letter);

/// @brief Free from heap a rotor
/// @param self The rotor to free
void free_Rotor(Rotor *self);

#endif