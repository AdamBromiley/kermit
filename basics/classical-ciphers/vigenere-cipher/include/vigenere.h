#ifndef VIGENERE_H
#define VIGENERE_H


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <getopt.h>

#include <parser.h>
#include <vigenere_cipher.h>


#define OPTSTRING ":ed"

#define READ_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE READ_BUFFER_SIZE


int usage(const char *programName);
int ioHandler(FILE *inputStream, FILE *outputStream, char *encryptionKey, enum VigenereMode encryptionMode);


#endif