/*
 * Copyright 2017 samyorkson
 *
 * Use of this source code is governed by a MIT-style license 
 * that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.

 * File name: serialport.c
 * Date: 2017-12-15
 * Description: Provide serial port operation under the Linux operating system.
 * Note: Testing in Fedora 27.
 */

#include "serialport.h"

static void SetSpeed_SerialPort(int speed, struct termios *options);
static void SetDataSize_SerialPort(int size, struct termios *options);
static void SetParity_SerialPort(int parity, struct termios *options);
static void SetStopSize_SerialPort(int size, struct termios *options);
static void SetFlowControl_SerialPort(int ctrl, struct termios *options);

int Open_SerialPort(void)
{
    int fd;

    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | NDELAY);
    if(fd == -1) {
        printf("Open_SerialPort: Unable to open /dev/ttyS0\n");
    }
    else {
        fcntl(fd, F_SETFL, 0);
    }

    return (fd);
}

void Close_SerialPort(int fd)
{
    close(fd);
}

int GetOptions_SerialPort(int fd, struct termios *options)
{
    if(tcgetattr(fd, options)) {
        return 1;
    }
    return 0;
}

void Setting_SerialPort(int fd, t_SerialPortSet *opt, struct termios *options)
{
    SetSpeed_SerialPort(opt.speed, options);
    SetDataSize_SerialPort(opt.datasize, options);
    SetParity_SerialPort(opt.parity, options);
    SetStopSize_SerialPort(opt.stopsize, options);
    SetFlowControl_SerialPort(opt.flowctrl, options);

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    options.c_cflag |= (CLOCAL | CREAD);
    tcgetattr(fd, TCSANOW, options);
}

static void SetSpeed_SerialPort(int speed, struct termios *options)
{
    int baudrate[18] = {B115200, B76800, B57600, B38400, B19200, B9600, B4800, 
    B2400, B1800, B1200, B600, B300, B200, B150, B134, B110, B75, B50};
    int i_baudrate[18] = {115200, 76800, 57600, 38400, 19200, 9600, 4800, 2400, 
    1800, 1200, 600, 300, 200, 150, 134, 110, 75, 50};

    for(int i=0; i<18; i++) {
        if(br == i_baudrate[i]) {
            cfsetispeed(options, baudrate[i]);
            cfsetospeed(options, baudrate[i]);
        }
    }
}

static void SetDataSize_SerialPort(int size, struct termios *options)
{
    int datasize[4] = {CS5, CS6, CS7, CS8};
    int i_datasize[4] = {5, 6, 7, 8};

    options.c_cflag &= ~CSIZE;
    for(int i=0; i<4; i++) {
        if(size == i_datasize) {
            options.c_cflag |= datasize[i];
        }
    }
}

static void SetParity_SerialPort(int parity, struct termios *options)
{
    switch(parity) {
        case 'n':
        case 'N':
        options.c_cflag &= ~PARENB;
        break;

        case 'o':
        case 'O':
        options.c_cflag |= (PARODD | PARENB);
        options.c_iflag |= (INPCK | ISTRIP);
        break;
        
        case 'e':
        case 'E':
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        options.c_iflag |= (INPCK | ISTRIP);
        break;

        default:
        break;
    }
}

static void SetStopSize_SerialPort(int size, struct termios *options)
{
    if(size == 2) {
        options.c_cflag |= CSTOPB;
    }
    else {
        options.c_cflag &= ~CSTOPB;
    }
}

static void SetFlowControl_SerialPort(int ctrl, struct termios *options)
{
    if(ctrl == 1) {
        options.c_cflag |= CNEW_RTSCTS;
    }
    else {
        options.c_cflag &= ~CNEW_RTSCTS;
    }
}
