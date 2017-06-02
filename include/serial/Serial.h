#ifndef SERIAL
#define SERIAL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

//Serial port function
int open_s(char* name);
int read_s(int fd, uint8_t *buffer, int nbyte);
int write_s(int fd, uint8_t *buffer, int nbyte);
int close_s(int fd);

int driveSpeed(int fd, int speed, uint8_t *buffer);
int driveMMS(int fd, int duration, uint8_t *buffer);
int stop(int fd, uint8_t *buffer);
int turn(int fd, int angle, uint8_t *buffer);

#endif
