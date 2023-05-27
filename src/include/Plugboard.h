#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "common.h"
#include "string.h"

/* Your definition of Plugboard */

typedef struct Plugboard {
    size_t num_pairs;
    char *pairs;
} Plugboard;

/// @brief  Creates a new plugboard
/// @param num_pairs The number of pairs of letter switches
/// @param pairs A string of pairs of letters to be switched; determined by groupings of 2
/// @return The new plugboard created
Plugboard *new_Plugboard(size_t num_pairs, const char *pairs);

/// @brief Apply character switching on a letter through a given plugboard
/// @param self The plugboard used for switching
/// @param letter Pointer to a letter to put through the plugboard
/// @return Address of character representing letter after plugboard
char *apply_Plugboard(Plugboard *self, char *letter);

/// @brief Free plugboard memory
/// @param self The plugboard to free
void free_Plugboard(Plugboard *self);

#endif
