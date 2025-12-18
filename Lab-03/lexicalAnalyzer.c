#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *removeComments(FILE *fp1)
{
    if (fp1 == NULL)
        return NULL;

    FILE *fp2 = fopen("removedComments.txt", "w");

    if (fp2 == NULL)
        return NULL;

    int ch, next;

    while ((ch = fgetc(fp1)) != EOF)
    {
        if (ch == '/')
        {
            next = fgetc(fp1);

            if (next == '/')
            {
                while ((ch = fgetc(fp1)) != EOF && ch != '\n')
                    ;
                // printf("\nSingle/Inline line comment ignored.");
            }
            else if (next == '*')
            {
                char prev = ' ';
                while ((ch = fgetc(fp1)) != EOF)
                {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                // printf("\nMulti line comment ignored.");
            }
            else
            {
                fputc('/', fp2);
                ungetc(next, fp1);
            }
        }
        else
        {
            fputc(ch, fp2);
        }
    }

    fclose(fp1);
    fclose(fp2);
    return fopen("removedComments.txt", "r");
}

int isKeyword(const char *word)
{
    const char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    int total = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < total; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int countKeywords(FILE *fp)
{
    char word[50];
    int ch, i, count = 0;

    rewind(fp);

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalpha(ch) || ch == '_')
        {
            i = 0;
            word[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
                word[i++] = ch;

            word[i] = '\0';

            if (isKeyword(word))
                count++;
        }
    }
    return count;
}

int countIdentifiers(FILE *fp)
{
    return 0;
}

int countConstants(FILE *fp)
{
    return 0;
}

int countSpecialSymbols(FILE *fp)
{
    return 0;
}

int countOperators(FILE *fp)
{
    return 0;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    fp = removeComments(fp);
    if (fp == NULL)
    {
        printf("Error removing comments.\n");
        return 1;
    }

    int keywordCount = countKeywords(fp);
    int identifierCount = countIdentifiers(fp);
    // int constantCount = countConstants(fp);
    // int specialSymbolCount = countSpecialSymbols(fp);
    // int operatorCount = countOperators(fp);
    printf("Keywords: %d\n", keywordCount);
    printf("Identifiers: %d\n", identifierCount);
    // printf("Constants: %d\n", constantCount);
    // printf("Special Symbols: %d\n", specialSymbolCount);
    // printf("Operators: %d\n", operatorCount);

    fclose(fp);
    return 0;
}