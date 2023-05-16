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

/// @brief Apply a reflector on a message
/// @param self The reflector to apply
/// @param message The message onto which to apply the reflector
/// @return The output of reflecting the message
char *apply_Reflector(Reflector *self, const char *message);

/// @brief Free from heap the data for a reflector
/// @param self The reflector to free
void free_Reflector(Reflector *self);

#endif