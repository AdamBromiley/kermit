#include <vigenere.h>


int main(int argc, char **argv)
{
    const char *programName = argv[0];

    enum VigenereMode encryptionMode = VIGENERE_NONE;
    char *encryptionKey;

    char *inputFilePath;
    FILE *inputFile;

    int optionID;
    int optionIndex;
    struct option longOptions[] =
    {
        {"d", no_argument, NULL, 'd'},
        {"e", no_argument, NULL, 'e'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    opterr = 0;

    while ((optionID = getopt_long(argc, argv, OPTSTRING, longOptions, &optionIndex)) != -1)
    {
        switch (optionID)
        {
            case 'd':
                if (encryptionMode == VIGENERE_ENCRYPT)
                {
                    fprintf(stderr, "%s: -%c: Option mutually exclusive with encrypt mode\n", programName, optionID);
                    return getoptErrorMessage(OPT_NONE, programName, 0, NULL);
                }
                
                encryptionMode = VIGENERE_DECRYPT;
                break;
            case 'e':
                if (encryptionMode == VIGENERE_DECRYPT)
                {
                    fprintf(stderr, "%s: -%c: Option mutually exclusive with decrypt mode\n", programName, optionID);
                    return getoptErrorMessage(OPT_NONE, programName, 0, NULL);
                }
                
                encryptionMode = VIGENERE_ENCRYPT;
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

    /* Get encryption key and input file */
    if (argc == optind + 1 || argc == optind + 2)
    {
        encryptionKey = argv[optind];

        if (argc == optind + 1)
        {
            inputFile = stdin;
        }
        else
        {
            inputFilePath = argv[optind + 1];

            if ((inputFile = fopen(inputFilePath, "rb")) == NULL)
            {
                fprintf(stderr, "%s: %s: Could not open file\n", programName, inputFilePath);
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        if (argc > optind)
        {
            return getoptErrorMessage(OPT_EARGC_HIGH, programName, 0, NULL);
        }
        else
        {
            return getoptErrorMessage(OPT_EARGC_LOW, programName, 0, NULL);
        }
    }

    /* Set encryption mode if unset */
    if (encryptionMode == VIGENERE_NONE)
    {
        encryptionMode = VIGENERE_ENCRYPT;
    }

    if (ioHandler(inputFile, stdout, encryptionKey, encryptionMode) != 0)
    {
        fprintf(stderr, "%s: Failed to complete operation\n", programName);
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    fclose(inputFile);

    return EXIT_SUCCESS;
}


/* Usage message for --help */
int usage(const char *programName)
{
    printf("Usage: %s [-d|-e] [KEY] [FILE]\n", programName);
    printf("       %s --help\n\n", programName);
    printf("Vigenere Cipher encrypt or decrypt FILE or standard input with KEY, to standard output.\n\n");
    printf("With no FILE, read standard input.\n\n");
    printf("Mandatory arguments to long options are mandatory for short options too.\n");
    printf("Cipher:\n");
    printf("  -d          Set mode to decrypt\n");
    printf("  -e          Set mode to encrypt (default)\n");
    printf("Miscellaneous:\n");
    printf("      --help  Display this help message and exit\n\n");

    return EXIT_SUCCESS;
}


/* Buffer input stream and encrypt */
int ioHandler(FILE *inputStream, FILE *outputStream, char *encryptionKey, enum VigenereMode encryptionMode)
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

        if (vigenereEncrypt(outputBuffer, readBuffer, readBytes, encryptionKey, strlen(encryptionKey), encryptionMode) != 0)
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