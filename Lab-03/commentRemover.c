#include <stdio.h>
void main()
{
    FILE *fp1 = fopen("input.txt", "r");
    FILE *fp2 = fopen("temp.txt", "w");

    char ch, p;
    while ((ch = fgetc(fp1)) != EOF)
    {
        if (ch == '/')
        {
            ch = fgetc(fp1);
            if (ch == '/')
            {
                while ((ch = fgetc(fp1)) != '\n')
                    ;
                printf("\nSingle/Inline line comment ignored");
            }
            else if (ch == '*')
            {
                while (1)
                {

                    p = ch;
                    ch = fgetc(fp1);
                    if (ch == '/' && p == '*')
                        break;
                }
                printf("\nMulti line comment ignored");
            }
            else
            {
                ungetc(ch, fp1);
                fputc('/', fp2);
            }
        }
        else
        {
            fputc(ch, fp2);
        }
    }
}