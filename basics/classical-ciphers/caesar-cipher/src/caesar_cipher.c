#include <caesar_cipher.h>


/* Encrypt/decrypt string using the Caesar Cipher */
int caesarEncrypt(char *inputBuffer, char *outputBuffer, size_t inputSize, int shift, enum CaesarMode mode)
{
    size_t i;

    char c;
    char baseChar;

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

    for (i = 0; i < inputSize; i++)
    {
        c = inputBuffer[i];

        /* Ignore non-alphabetic characters */
        if (isalpha(c) != 0)
        {
            baseChar = isupper(c) ? BASE_UPPER : BASE_LOWER;

            /* Get index of c in the alphabet */
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

        outputBuffer[i] = c;
    }

    return 0;
}