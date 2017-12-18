/*
 * Copyright 2017 samyorkson
 *
 * Use of this source code is governed by a MIT-style license 
 * that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.

 * File name: serialport.h
 * Date: 2017-12-15
 * Description: Provide serial port operation under the Linux operating system.
 * Note: Testing in Fedora 27.
 */

#ifndef __INC_SERIAL_PORT_H__
#define __INC_SERIAL_PORT_H__

/* Including needed system library. */
#include <stdio.h>      //Standard input/output definitions.
#include <stdlib.h>     //Standard function library definition.
#include <string.h>     //String function definitions.
#include <unistd.h>     //UNIX standard function definitions.
#include <fcntl.h>      //File control definitions.
#include <termios.h>    //POSIX terminal control definitions.
#include <errno.h>      //Error number definitions.
#include <sys/types.h>  //Basic system data types of UNIX definitions.
#include <sys/stat.h>   //File status UNIX definitions.

/* Operate SerialPort function */
extern int Open_SerialPort(void);
extern void Close_SerialPort(int fd);
extern int GetOptions_SerialPort(int fd, struct termios *options);
extern void Setting_SerialPort(int fd, t_SerialPortSet *opt, 
struct termios *options);

/* Defining the type of serial port settings */
typedef struct t_SerialPortSet {
    int speed;
    int datasize;
    int parity;
    int stopsize;
    int flowctrl;
};


#endif
