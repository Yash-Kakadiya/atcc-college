%option noyywrap

%{
#include <stdio.h>

int chars = 0;
int words = 0;
int lines = 0;
%}

%%
\n              { lines++; chars++; }
[ \t]+          { chars += yyleng; }
[A-Za-z0-9]+    { words++; chars += yyleng; }
.               { chars++; }
%%

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("Cannot open file\n");
        return 1;
    }

    yyin = fp;
    yylex();

    printf("\nNumber of characters = %d", chars);
    printf("\nNumber of words      = %d", words);
    printf("\nNumber of lines      = %d\n", lines);

    fclose(fp);
    return 0;
}
