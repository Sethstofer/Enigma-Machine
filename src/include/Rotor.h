#ifndef ROTOR_H
#define ROTOR_H

#include "common.h"
#include "stdlib.h"

/* Your definition of Rotor */

typedef struct Rotor {
    char *rotorConfig;
    size_t ringDelta;
    size_t offset;
} Rotor;

/// @brief Create a new rotor
/// @param rotorConfig The letter configuration of the rotor
/// @param init The set offset from start of rotorConfig
/// @param ring The number representing the ring offset of the rotor
/// @return The created rotor
Rotor *new_Rotor(const char *rotorConfig, size_t init, size_t ring);

/// @brief Apply the rotors, first to last, on a letter
/// @param rotors The rotors to apply
/// @param num_rotors The number of rotors provided
/// @param letter Address of letter to go through the rotors
/// @return Address of cipher result from applying the rotors forwardly
char *apply_Rotors_frwd(Rotor **rotors, size_t num_rotors, char *letter);

/// @brief Apply the rotors, last to first, on a letter after reflection
/// @param rotors The rotors to apply
/// @param num_rotors The number of rotors provided
/// @param letter Address of letter to go through the rotors
/// @return Address of cipher result from applying the rotors backwardly
char *apply_Rotors_bkwd(Rotor **rotors, size_t num_rotors, char *letter);

/// @brief Free from heap a rotor
/// @param self The rotor to free
void free_Rotor(Rotor *self);

#endif
