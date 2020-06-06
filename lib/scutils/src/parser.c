#include <parser.h>


/* Convert error code to message when parsing command line arguments */
int getoptErrorMessage(enum GetoptError optionError, char *programName, char shortOption, char *longOption)
{
    switch (optionError)
    {
        case OPT_NONE:
            break;
        case OPT_ERROR:
            fprintf(stderr, "%s: Unknown error when reading command-line options\n", programName);
            break;
        case OPT_EOPT:
            if (shortOption == 0)
            {
                fprintf(stderr, "%s: Invalid option: \'%s\'\n", programName, longOption);
            }
            else
            {
                fprintf(stderr, "%s: Invalid option: \'-%c\'\n", programName, shortOption);
            }
            break;
        case OPT_ENOARG:
            fprintf(stderr, "%s: -%c: Option argument required\n", programName, shortOption);
            break;
        case OPT_EARG:
            fprintf(stderr, "%s: -%c: Failed to parse argument\n", programName, shortOption);
            break;
        case OPT_EARGC_LOW:
            fprintf(stderr, "%s: Too few arguments supplied\n", programName);
            break;
        case OPT_EARGC_HIGH:
            fprintf(stderr, "%s: Too many arguments supplied\n", programName);
            break;
        default:
            break;
    }

    fprintf(stderr, "Try \'%s --help\' for more information\n", programName);
    return EXIT_FAILURE;
}


/* Convert string to long int and handle errors */
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
        /* More characters in string (might not be considered an error) */
        return STRTOL_EEND;
    }

    return STRTOL_NONE;
}