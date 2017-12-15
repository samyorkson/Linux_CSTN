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

int Open_SerialPort(void)
{
    int fd;

    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | NDELAY);
    if(fd == -1) {
        perror("Open_SerialPort: Unable to open /dev/ttyS0 -");
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