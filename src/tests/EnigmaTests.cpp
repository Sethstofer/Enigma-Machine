extern "C" {
#include "Enigma.h"
#include "common.h"
}
#include <gtest/gtest.h>

namespace {
/* Your tests for Enigma here. */
    
    Enigma *get_default_Enigma() {
        const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
        size_t rings[] = {1, 5, 3};
        size_t inits[] = {1, 5, 3};
        return new_Enigma(3, rotors, rings, inits, I_UKW_A, 5, "ECSONFIVTH");
    }

    TEST(Self, OneRotor) {
    const char *rotors[] = {ROTOR_I};
    size_t rings[] = {0};
    size_t inits[] = {0};
    Enigma *enigma = new_Enigma(1, rotors, rings, inits, I_UKW_A, 0, NULL);
    char encrypt[] = "\0\0\0\0";
    encrypt_Enigma(enigma, encrypt, "C");
    free_Enigma(enigma);
    }

    TEST(Self, Integral) {
        Enigma *enigma = get_default_Enigma();
        char encrypt[64];
        memset(encrypt, 0, 64);
        encrypt_Enigma(enigma, encrypt, "HELLO");
        EXPECT_STREQ(encrypt, "INNBE");
        size_t inits[] = {1, 5, 3};
        reset_rotor_Enigma(enigma, inits);
        char decrypt[64];
        memset(decrypt, 0, 64);
        encrypt_Enigma(enigma, decrypt, encrypt);
        EXPECT_STREQ("HELLO", decrypt);
        free_Enigma(enigma);
    }
    
}