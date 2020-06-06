#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H


#include <stdio.h>
#include <ctype.h>


#define ROT13_SHIFT 13

#define BASE_UPPER 'A'
#define BASE_LOWER 'a'
#define ALPHABET_LENGTH 26


enum Mode
{
        MODE_NONE,
        MODE_ENCRYPT,
        MODE_DECRYPT,
        MODE_ROT13
};


int caesarEncrypt(char *inputBuffer, char *outputBuffer, size_t inputSize, int shift, enum Mode caesarMode);


#endif