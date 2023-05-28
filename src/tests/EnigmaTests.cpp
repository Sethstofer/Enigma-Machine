extern "C" {
#include "Enigma.h"
#include "common.h"
}
#include <gtest/gtest.h>

namespace {
/* Your tests for Enigma here. */
    /*
    Enigma *get_default_Enigma() {
        const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
        size_t rings[] = {1, 5, 3};
        size_t inits[] = {1, 5, 3};
        return new_Enigma(3, rotors, rings, inits, I_UKW_A, 5, "ECSONFIVTH");
    }

    TEST(Self, Integral) {
        Enigma *enigma = get_default_Enigma();
        char encrypt[64];
        memset(encrypt, 0, 64);
        encrypt_Enigma(enigma, encrypt, "HELLO");
        EXPECT_STREQ(encrypt, "ICUBA");
        size_t inits[] = {1, 5, 3};
        reset_rotor_Enigma(enigma, inits);
        char decrypt[64];
        memset(decrypt, 0, 64);
        encrypt_Enigma(enigma, decrypt, encrypt);
        EXPECT_STREQ("HELLO", decrypt);
        free_Enigma(enigma);
    }
    */
}