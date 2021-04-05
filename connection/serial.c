#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

#define ARDUINO_TTY "/dev/ttyACM0"

bool g_running = true;
bool new_command = false;

void handle_signal(int sig){
    g_running = false;
}

int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        if (tcgetattr (fd, &tty) != 0)
        {
            fprintf(stdout, "error %d from tcgetattr\n", errno);
            return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
            fprintf(stdout, "error %d from tcsetattr\n", errno);
            return -1;
        }
        return 0;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                fprintf(stdout, "error %d from tggetattr\n", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0){
            fprintf(stdout, "error %d setting term attributes\n", errno);
        }
}



int main(){

    signal(SIGINT, handle_signal);

    int len;
    char cmd[100];
    char message[100];

    chmod(ARDUINO_TTY, S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR);
    int arduino = open(ARDUINO_TTY, O_RDWR | O_NOCTTY | O_SYNC);
    if(arduino < 0){
        fprintf(stdout, "Failed to open file %d, %s\n", errno, strerror(errno));
        return 0;
    }

    set_interface_attribs (arduino, B9600, 0);  // set speed to 9600 bps, 8n1 (no parity)
    set_blocking (arduino, 0);                // set no blocking

    while(g_running){
        new_command = issue_command();

        if(new_command){
            len = read(arduino, message, 100);
            if(len > 0){
                fprintf(stdout, "Message from Arduino : %s\n", message);
            }
            new_command = false;
        }
        memset(message, '\0', 100);
    }
    close(arduino);
    return 0;
}
