#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "common.h"

/* Your definition of Reflector */
typedef struct Reflector {
    char *reflections;
} Reflector;

/// @brief Create a new reflector
/// @param reflections The reflections off which to create reflector
/// @return Pointer to the new reflector
Reflector *new_Reflector(const char *reflections);

/// @brief Apply a reflector on a letter
/// @param self The reflector to apply
/// @param letter The letter to put through reflector
/// @return Address of reflected letter
char *apply_Reflector(Reflector *self, char *letter);

/// @brief Free from heap the data for a reflector
/// @param self The reflector to free
void free_Reflector(Reflector *self);

#endif
