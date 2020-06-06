#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H


#include <stddef.h>
#include <ctype.h>


#define BASE_UPPER 'A'
#define BASE_LOWER 'a'
#define ALPHABET_LENGTH 26


enum VigenereMode
{
    VIGENERE_NONE,
    VIGENERE_ENCRYPT,
    VIGENERE_DECRYPT
};


int vigenereEncrypt(char *ciphertext, const char *plaintext, size_t plaintextSize, char *key, size_t keyLength, enum VigenereMode mode);


#endif