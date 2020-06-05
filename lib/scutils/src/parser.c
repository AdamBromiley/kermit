#include <parser.h>


int stringToLong(char *buffer, long int *x, long int xMin, long int xMax, int base)
{
    char *endptr;

    if ((base < 2 && base != 0) || base > 36)
    {
        return STRTOL_EBASE;
    }

    errno = 0;

    *x = strtol(buffer, &endptr, base);
    
    if (endptr == buffer || errno == EINVAL)
    {
        /* Failed to convert */
        return STRTOL_ERROR;
    }
    else if (errno == ERANGE)
    {
        /* Out of range of long int */
        return STRTOL_ERANGE;
    }
    else if (*x < xMin)
    {
        return STRTOL_EMIN;
    }
    else if (*x > xMax)
    {
        return STRTOL_EMAX;
    }
    else if (*endptr != '\0')
    {
        /* More characters in string */
        return STRTOL_EEND;
    }

    return 0;
}