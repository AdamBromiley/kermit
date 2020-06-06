#ifndef CAESAR_H
#define CAESAR_H


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <getopt.h>
#include <limits.h>

#include <parser.h>
#include <caesar_cipher.h>


#define OPTSTRING ":des:"

#define SHIFT_DEFAULT 3
#define SHIFT_MIN INT_MIN
#define SHIFT_MAX INT_MAX

#define READ_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE READ_BUFFER_SIZE


int usage(const char *programName);
int ioHandler(FILE *inputStream, FILE *outputStream, int encryptionShift, enum CaesarMode encryptionMode);


#endif