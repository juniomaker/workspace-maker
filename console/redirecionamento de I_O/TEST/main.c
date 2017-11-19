#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEVICE_OUT freopen("/dev/ttyS0", "wb", stdout)
#define __DEVICE_IN freopen("/dev/ttyS0", "rb", stdin)
#define __CONSOLE_OUT freopen("/dev/tty","wb", stdout)
#define __CONSOLE_IN freopen("/dev/tty","rb", stdin)

int main()
{
    char str[80];
    //FILE *fp;

    while(1)
    {
        printf("digite um comando: ");
        __CONSOLE_IN;
        gets(str);
        //strcat(str, "\n");
        __DEVICE_OUT;
        printf(str);

         __DEVICE_IN;
        gets(str);
        //strcat(str, "\n");

        __CONSOLE_OUT;
        printf(str);
        puts("\n");


    }
    return 0;
}
