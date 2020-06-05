#include <caesar.h>


int main(int argc, char **argv)
{
    int result;

    int rot13Flag = 0;
    enum Mode encryptionMode = NONE;
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
                if (encryptionMode == ENCRYPT)
                {
                    fprintf(stderr, "%s: -%c: Option mutually exclusive with encrypt mode\n", argv[0], optionID);
                    return EXIT_FAILURE;
                }
                
                encryptionMode = DECRYPT;
                break;
            case 'e':
                if (encryptionMode == DECRYPT)
                {
                    fprintf(stderr, "%s: -%c: Option mutually exclusive with decrypt mode\n", argv[0], optionID);
                    return EXIT_FAILURE;
                }
                
                encryptionMode = ENCRYPT;
                break;
            case 's':
                result = stringToLong(optarg, &encryptionShift, SHIFT_MIN, SHIFT_MAX, 10);
                
                if (result != 0)
                {
                    if (result == STRTOL_ERANGE || result == STRTOL_EMIN || result == STRTOL_EMAX)
                    {
                        fprintf(stderr, "%s: -%c: Encryption shift out of range, it must be between %d and %d\n", 
                            argv[0], optionID, SHIFT_MIN, SHIFT_MAX);
                    }
                    else if (result == STRTOL_ERROR || result == STRTOL_EEND)
                    {
                        fprintf(stderr, "%s: -%c: Invalid encryption shift\n", argv[0], optionID);
                    }
                    else
                    {
                        fprintf(stderr, "%s: -%c: Failed to parse encryption shift\n", argv[0], optionID);
                    }

                    return EXIT_FAILURE;
                }

                break;
            case 'h':
                if (argc != 2)
                {
                    fprintf(stderr, "%s: --help: Option is mutually exclusive with all other options\n", argv[0]);
                    return EXIT_FAILURE;
                }

                printf("Usage: %s [-d|-e] [-s SHIFT] [FILE]\n", argv[0]);
                printf("       %s --rot13 [FILE]\n", argv[0]);
                printf("       %s --help\n\n", argv[0]);
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
            case '?':
                if (optopt == 0)
                {
                    fprintf(stderr, "%s: Invalid option: \'%s\'\n", argv[0], argv[optind - 1]);
                }
                else
                {
                    fprintf(stderr, "%s: Invalid option: \'-%c\'\n", argv[0], optopt);
                }
                return EXIT_FAILURE;
            case ':':
                fprintf(stderr, "%s: -%c: Option argument required\n", argv[0], optopt);
                return EXIT_FAILURE;
            default:
                fprintf(stderr, "%s: Unknown error when reading command-line options\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (encryptionMode == NONE)
    {
        encryptionMode = ENCRYPT;
    }

    if (rot13Flag != 0)
    {
        encryptionMode = ROT13;
    }

    if (optind == argc)
    {
        inputFile = stdin;
    }
    else if (optind == argc - 1)
    {
        inputFilePath = argv[optind];

        if ((inputFile = fopen(inputFilePath, "rb")) == NULL)
        {
            fprintf(stderr, "%s: Could not open input file \"%s\"\n", argv[0], inputFilePath);
            return EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "%s: Too many operands\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (ioHandler(inputFile, stdout, encryptionShift, encryptionMode) != 0)
    {
        fprintf(stderr, "%s: Failed to complete operation\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int ioHandler(FILE *inputStream, FILE *outputStream, int encryptionShift, enum Mode encryptionMode)
{
    size_t readBytes;

    char readBuffer[READ_BUFFER_SIZE];
    char outputBuffer[OUTPUT_BUFFER_SIZE];

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