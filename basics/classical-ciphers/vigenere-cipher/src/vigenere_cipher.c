#include <vigenere_cipher.h>


/* Encrypt/decrypt string using the Vigenere Cipher */
int vigenereEncrypt(char *ciphertext, const char *plaintext, size_t plaintextSize, char *key, size_t keyLength, enum VigenereMode mode)
{
    size_t i;
    char c, k, baseChar;
    int shift;

    /* Convert key to uppercase and check for non-alphabetic characters */
    for (i = 0; i < keyLength; ++i)
    {
        k = key[i];

        if (isalpha(k) == 0)
        {
            return 1;
        }

        key[i] = toupper(k);
    }


    for (i = 0; i < plaintextSize; ++i)
    {
        c = plaintext[i];

        /* Ignore non-alphabetic characters */
        if (isalpha(c) != 0)
        {
            /* Get respective key character */
            k = key[i % keyLength];

            /* Get index of k in the alphabet */
            shift = k - BASE_UPPER;

            if (mode == VIGENERE_DECRYPT)
            {
                shift = -(shift);
            }

            /* Get index of c in the alphabet */
            baseChar = isupper(c) ? BASE_UPPER : BASE_LOWER;
            c -= baseChar;

            /* Add shift */
            c = (c + shift) % ALPHABET_LENGTH;

            /* If decrypting and c goes below 0 (% is not modulo) */
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