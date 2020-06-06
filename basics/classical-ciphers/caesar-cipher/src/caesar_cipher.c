#include <caesar_cipher.h>


/* Encrypt/decrypt string using the Caesar Cipher */
int caesarEncrypt(char *ciphertext, const char *plaintext, size_t plaintextSize, int shift, enum CaesarMode mode)
{
    size_t i;
    char c, baseChar;

    switch (mode)
    {
        case CAESAR_ENCRYPT:
            break;
        case CAESAR_DECRYPT:
            shift = -(shift);
            break;
        case CAESAR_ROT13:
            shift = ROT13_SHIFT;
            break;
        default:
            return 1;
    }

    for (i = 0; i < plaintextSize; ++i)
    {
        c = plaintext[i];

        /* Ignore non-alphabetic characters */
        if (isalpha(c) != 0)
        {
            /* Get index of c in the alphabet */
            baseChar = isupper(c) ? BASE_UPPER : BASE_LOWER;
            c -= baseChar;

            /* Add shift */
            c = (c + shift) % ALPHABET_LENGTH;

            /* If shift is negative and c goes below 0 (% is not modulo) */
            if (c < 0)
            {
                c += ALPHABET_LENGTH;
            }

            /* Convert alphabet index back to ASCII char */
            c += baseChar;
        }

        ciphertext[i] = c;
    }

    return 0;
}