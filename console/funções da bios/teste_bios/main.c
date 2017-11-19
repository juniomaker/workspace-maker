#include <stdio.h>
#include <stdlib.h>
#include <bios.h>

int main()
{
    long t;

    _bios_timeofday(0, &t);

    printf("Valor do relogio: 1%d", t);
    return 0;
}
