#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


enum GetoptError
{
    OPT_NONE,
    OPT_ERROR,
    OPT_EOPT,
    OPT_ENOARG,
    OPT_EARG,
    OPT_EARGC_LOW,
    OPT_EARGC_HIGH
};

enum strtolError
{
    STRTOL_NONE,
    STRTOL_EBASE,
    STRTOL_ERROR,
    STRTOL_ERANGE,
    STRTOL_EMIN,
    STRTOL_EMAX,
    STRTOL_EEND
};


int getoptErrorMessage(enum GetoptError optionError, const char *programName, char shortOption, const char *longOption);
int stringToLong(const char *buffer, long int *x, long int xMin, long int xMax, int base);


#endif