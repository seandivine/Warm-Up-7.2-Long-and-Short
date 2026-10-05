#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[])
{
    FILE *source;
    FILE *shortFile;
    FILE *longFile;

    char line[MAX_LINE_LENGTH];
    int shortCount = 0;
    int longCount = 0;

    /* Program name plus three filenames are required. */
    if (argc != 4)
    {
        fprintf(stderr,
                "Usage: %s source_file short_file long_file\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    source = fopen(argv[1], "r");

    if (source == NULL)
    {
        fprintf(stderr, "Unable to open %s for reading.\n", argv[1]);
        return EXIT_FAILURE;
    }

    shortFile = fopen(argv[2], "w");

    if (shortFile == NULL)
    {
        fprintf(stderr, "Unable to open %s for writing.\n", argv[2]);
        fclose(source);
        return EXIT_FAILURE;
    }

    longFile = fopen(argv[3], "w");

    if (longFile == NULL)
    {
        fprintf(stderr, "Unable to open %s for writing.\n", argv[3]);
        fclose(source);
        fclose(shortFile);
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), source) != NULL)
    {
        size_t length = strlen(line);
        size_t comparisonLength = length;

        /* Do not count the line-ending character as part of the line. */
        if (comparisonLength > 0 &&
            line[comparisonLength - 1] == '\n')
        {
            comparisonLength--;
        }

        if (comparisonLength > 0 &&
            line[comparisonLength - 1] == '\r')
        {
            comparisonLength--;
        }

        if (comparisonLength < 20)
        {
            for (size_t i = 0; i < length; i++)
            {
                line[i] = (char)toupper((unsigned char)line[i]);
            }

            fputs(line, shortFile);
            shortCount++;
        }
        else
        {
            for (size_t i = 0; i < length; i++)
            {
                line[i] = (char)tolower((unsigned char)line[i]);
            }

            fputs(line, longFile);
            longCount++;
        }
    }

    fclose(source);
    fclose(shortFile);
    fclose(longFile);

    printf("%d lines written to %s\n", shortCount, argv[2]);
    printf("%d lines written to %s\n", longCount, argv[3]);

    return EXIT_SUCCESS;
}