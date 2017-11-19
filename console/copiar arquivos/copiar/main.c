#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *in, *out;
    char ch;

    if(argc != 3)
    {
        printf(" arquivo origem ou destino n informado!\n");
        exit(1);
    }

    if((in=fopen(argv[1], "rb"))==NULL)
    {
        printf(" arquivo n pode ser aberto!\n");
        exit(1);
    }

    if((out=fopen(argv[2], "wb"))==NULL)
    {
        printf(" arquivo destino n pode ser aberto!\n");
        exit(1);
    }

    while(!feof(in))
    {
        ch = getc(in);
        if(ferror(in))
        {
            puts("erro ao ler o arquivo!\n");
            clearerr(in);
            break;
        }
        else
        {
            if(!feof(in)) putc(ch, out);
            if(ferror(out))
            {
                puts("erro ao copiar o arquivo!\n");
                clearerr(out);
                break;
            }
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}
