#include <caesar_cipher.h>


int caesarEncrypt(char *inputBuffer, char *outputBuffer, size_t inputSize, int shift, enum Mode caesarMode)
{
    size_t i;

    char c;
    char baseChar;

    switch (caesarMode)
    {
        case ENCRYPT:
            break;
        case DECRYPT:
            shift = -(shift);
            break;
        case ROT13:
            shift = ROT13_SHIFT;
            break;
        default:
            return 1;
    }

    for (i = 0; i < inputSize; i++)
    {
        c = inputBuffer[i];

        if (isalpha(c) != 0)
        {
            baseChar = isupper(c) ? BASE_UPPER : BASE_LOWER;

            c -= baseChar;
            c = (c + shift) % ALPHABET_LENGTH;
            if (c < 0)
            {
                c += ALPHABET_LENGTH;
            }
            c += baseChar;
        }

        outputBuffer[i] = c;
    }

    return 0;
}