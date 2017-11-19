#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

char buffer[255];

int open_port()
{
    int fd; /*File descriptor for the port*/
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1)
    {
        perror("open_port: Unable to open /dev/ttyS0 - ");
    }
    else
    {
        fcntl(fd, F_SETFL, 0);
    }
    return(fd);
}

void serial_setup(int fd)
{
    struct termios options;

    /* Get the current options for the port */
    tcgetattr(fd,&options);

    /* Set the baud rates to 9600 */
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    /* Enable the receiver and set local mode */
    options.c_cflag |= (CLOCAL | CREAD);
    /* Set the new options for the port */
    tcsetattr(fd, TCSANOW, &options);
    return;
}

void clr_buffer()
{
    unsigned char index;
    for(index=0; index<255; ++index)
    {
        buffer[index] = '\0';
    }
}

void clr_buffer_teclado()
{
    char ch;
    while((ch = getchar())!= '\n');
}

int main()
{
    int device, n;

    device = open_port();
    serial_setup(device);
    printf("#########################################################################\n");
    printf("____________________________TERMINAL TTYS0_______________________________\n");
    puts("\n");

    while(1)
    {
        //device = open_port();
        //serial_setup(device);
        clr_buffer();
        printf(">> ");
        fgets(buffer,10,stdin);
        clr_buffer_teclado();

        n = write(device, buffer, 9);
        if(n < 0) fputs("write() of 9 bytes failed!\n", stderr);

        n = read(device, buffer, 255) ;
        if(n < 0)
        {
            perror("read() of bytes failed!\n");
        }
        else
        {
            unsigned char i;
            for(i=0; i<n; ++i)
            {
                putc(buffer[i],stdout);
            }
        }
        //close(device);
    }
    close(device);
    return 0;
}
