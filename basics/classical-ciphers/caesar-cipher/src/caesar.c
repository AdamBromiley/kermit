#include <caesar.h>


int main(int argc, char **argv)
{
    char *programName = argv[0];

    int result;

    int rot13Flag = 0;
    enum CaesarMode encryptionMode = CAESAR_NONE;
    long int encryptionShift = SHIFT_DEFAULT;
    
    char *inputFilePath;
    FILE *inputFile;

    int optionID;
    int optionIndex;
    struct option longOptions[] =
    {
        {"d", no_argument, NULL, 'd'},
        {"e", no_argument, NULL, 'e'},
        {"rot13", no_argument, &rot13Flag, 1},
        {"shift", required_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    opterr = 0;

    while ((optionID = getopt_long(argc, argv, OPTSTRING, longOptions, &optionIndex)) != -1)
    {
        switch (optionID)
        {
            case 0:
                break;
            case 'd':
                if (encryptionMode == CAESAR_ENCRYPT)
                {
                    fprintf(stderr, "%s: -%c: Option mutually exclusive with encrypt mode\n", programName, optionID);
                    return getoptErrorMessage(OPT_NONE, programName, 0, NULL);
                }
                
                encryptionMode = CAESAR_DECRYPT;
                break;
            case 'e':
                if (encryptionMode == CAESAR_DECRYPT)
                {
                    fprintf(stderr, "%s: -%c: Option mutually exclusive with decrypt mode\n", programName, optionID);
                    return getoptErrorMessage(OPT_NONE, programName, 0, NULL);
                }
                
                encryptionMode = CAESAR_ENCRYPT;
                break;
            case 's':
                result = stringToLong(optarg, &encryptionShift, SHIFT_MIN, SHIFT_MAX, 10);
                
                if (result != STRTOL_NONE)
                {
                    if (result == STRTOL_ERANGE || result == STRTOL_EMIN || result == STRTOL_EMAX)
                    {
                        fprintf(stderr, "%s: -%c: Encryption shift out of range, it must be between %d and %d\n", 
                            programName, optionID, SHIFT_MIN, SHIFT_MAX);
                    }
                    else if (result == STRTOL_ERROR || result == STRTOL_EEND)
                    {
                        fprintf(stderr, "%s: -%c: Invalid encryption shift\n", programName, optionID);
                    }
                    else
                    {
                        return getoptErrorMessage(OPT_EARG, programName, optionID, NULL);
                    }

                    return getoptErrorMessage(OPT_NONE, programName, 0, NULL);
                }

                break;
            case 'h':
                return usage(programName);
            case '?':
                return getoptErrorMessage(OPT_EOPT, programName, optopt, argv[optind - 1]);
            case ':':
                return getoptErrorMessage(OPT_ENOARG, programName, optopt, NULL);
            default:
                return getoptErrorMessage(OPT_ERROR, programName, 0, NULL);
        }
    }

    /* Get input file */
    if (optind == argc)
    {
        inputFile = stdin;
    }
    else if (optind == argc - 1)
    {
        inputFilePath = argv[optind];

        if ((inputFile = fopen(inputFilePath, "rb")) == NULL)
        {
            fprintf(stderr, "%s: %s: Could not open file\n", programName, inputFilePath);
            return EXIT_FAILURE;
        }
    }
    else
    {
        return getoptErrorMessage(OPT_EARGC_HIGH, programName, 0, NULL);
    }

    /* Set encryption mode if unset (or --rot13) */
    if (rot13Flag != 0)
    {
        encryptionMode = CAESAR_ROT13;
    }
    else if (encryptionMode == CAESAR_NONE)
    {
        encryptionMode = CAESAR_ENCRYPT;
    }

    if (ioHandler(inputFile, stdout, encryptionShift, encryptionMode) != 0)
    {
        fprintf(stderr, "%s: Failed to complete operation\n", programName);
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fclose(inputFile);

    return EXIT_SUCCESS;
}


/* Usage message for --help */
int usage(char *programName)
{
    printf("Usage: %s [-d|-e] [-s SHIFT] [FILE]\n", programName);
    printf("       %s --rot13 [FILE]\n", programName);
    printf("       %s --help\n\n", programName);
    printf("Caesar Cipher encrypt or decrypt FILE or standard input, to standard output.\n\n");
    printf("With no FILE, read standard input.\n\n");
    printf("Mandatory arguments to long options are mandatory for short options too.\n");
    printf("Cipher:\n");
    printf("  -d                       Set mode to decrypt\n");
    printf("  -e                       Set mode to encrypt (default)\n");
    printf("            --rot13        Use a shift of 13 - overrides cipher mode and SHIFT\n");
    printf("  -s SHIFT, --shift=SHIFT  Specify cipher shift amount\n");
    printf("                           [+] Default = 3\n\n");
    printf("Miscellaneous:\n");
    printf("            --help         Display this help message and exit\n\n");

    return EXIT_SUCCESS;
}


/* Buffer input stream and encrypt */
int ioHandler(FILE *inputStream, FILE *outputStream, int encryptionShift, enum CaesarMode encryptionMode)
{
    size_t readBytes;

    char readBuffer[READ_BUFFER_SIZE];
    char outputBuffer[OUTPUT_BUFFER_SIZE];

    /* Keep on reading unless error or EOF */
    do
    {
        readBytes = fread(readBuffer, sizeof(char), sizeof(readBuffer) / sizeof(char), inputStream);

        if (ferror(inputStream) != 0)
        {
            return 1;
        }

        if (readBytes == 0)
        {
            continue;
        }

        if (caesarEncrypt(readBuffer, outputBuffer, readBytes, encryptionShift, encryptionMode) != 0)
        {
            return 1;
        }

        if (fwrite(outputBuffer, sizeof(char), readBytes, outputStream) != readBytes)
        {
            return 1;
        }

        fflush(outputStream);
    } while (readBytes == sizeof(readBuffer) && feof(inputStream) == 0);
    
    return 0;
}