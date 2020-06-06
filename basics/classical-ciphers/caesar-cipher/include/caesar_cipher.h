#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H


#include <stdio.h>
#include <ctype.h>


#define ROT13_SHIFT 13

#define BASE_UPPER 'A'
#define BASE_LOWER 'a'
#define ALPHABET_LENGTH 26


enum CaesarMode
{
        CAESAR_NONE,
        CAESAR_ENCRYPT,
        CAESAR_DECRYPT,
        CAESAR_ROT13
};


int caesarEncrypt(char *inputBuffer, char *outputBuffer, size_t inputSize, int shift, enum CaesarMode mode);


#endif