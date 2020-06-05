#ifndef PARSER_H
#define PARSER_H


#include <stdlib.h>
#include <errno.h>


enum strtolError
{
        STRTOL_EBASE = 1,
        STRTOL_ERROR = 2,
        STRTOL_ERANGE = 3,
        STRTOL_EMIN = 4,
        STRTOL_EMAX = 5,
        STRTOL_EEND = 6
};


int stringToLong(char *buffer, long int *x, long int xMin, long int xMax, int base);


#endif