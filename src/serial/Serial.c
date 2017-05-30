#include "../../include/serial/Serial.h"

#define DEBUG

int open_s(char *name){

	struct termios toptions ;
	int fd;

	#ifdef DEBUG
	printf("Open serial : %s\n", name) ;
	#endif

	if((fd = open(name, O_RDWR | O_NONBLOCK))== -1){
		printf("Error opening %s\n", name);
		return -1;
	}

	#ifdef DEBUG
	printf("wait\n") ;
	#endif

	if(tcgetattr(fd, &toptions) == -1){
		printf("Error getting attribut from  %s\n", name);
		return -1;
	}

	/* 9600 baud */
	cfsetispeed(&toptions, B9600) ;
	cfsetospeed(&toptions, B9600) ;

	/* 8 bits, no parity, no stop bits */
	toptions.c_cflag &= ~PARENB ;
	toptions.c_cflag &= ~CSTOPB ;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8 ;

	/* no hardware flow control */
	toptions.c_cflag &= ~CRTSCTS;

	toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
  toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

  toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
  toptions.c_oflag &= ~OPOST; // make raw


	toptions.c_cc[VMIN]  = 0;
	toptions.c_cc[VTIME] = 0;

	if(tcsetattr(fd, TCSANOW, &toptions) == -1){
		printf("Error setting attribut to %s\n", name);
		return -1;
	}

	usleep(1000*1000);

	tcflush(fd, TCIFLUSH);

	#ifdef DEBUG
	printf("Serial port open\n") ;
	#endif

	return fd;
}

int close_s(int fd){
	#ifdef DEBUG
		printf("Close serial : %d\n", fd);
	#endif
	return close(fd);
}

int write_s(int fd, uint8_t *buffer, int nbyte){

	#ifdef DEBUG
		printf("Envoi de la commande : %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	#endif

	int val;
	val= write(fd, buffer, nbyte);

	return val;
}

int read_s(int fd, uint8_t *buffer, int nbyte){
	uint8_t* car = (uint8_t*)malloc(1);
	if(read(fd,car,0) == -1){
		printf("Erreur reading file");
		free(car);
		return -1;
	}
	while(*car != '#'){
		read(fd,car,1);
	}
	int cpt=0;
	while(*car != '!' && cpt < nbyte){
		if(read(fd, car, 1) == 1){
			*(buffer + cpt) = *car;
			cpt++;
		}
	}
	free(car);

	#ifdef DEBUG
		printf("Reception de %s de l'arduino %d\n", buffer, fd);
	#endif
	return 1;
}

int driveSpeed(int fd, int speed, uint8_t *buffer){

	buffer[0] = 'm';

	buffer[1] = 43;
	if(speed < 0 ){
		buffer[1] = 45;
		speed = -speed;
	}

	buffer[2] = (speed >> 8) & 255;
	buffer[3] = speed & 255;

	int val = write_s(fd, buffer, 4);

	return val;
}

int stop(int fd, uint8_t *buffer){
	buffer[0] = 's';
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;

	int val = write_s(fd, buffer, 4);

	return val;
}

int driveMMS(int fd, int duration, uint8_t *buffer){
	buffer[0] = 'd';

	buffer[1] = 43;
	if(duration < 0 ){
		buffer[1] = 45;
		duration = -duration;
	}

	buffer[2] = (duration >> 8) & 255;
	buffer[3] = duration & 255;

	int val = write_s(fd, buffer, 4);

	return val;
}

int turn(int fd, int angle, uint8_t *buffer){
	buffer[0] = 't';

	buffer[1] = 43;
	if(angle < 0 ){
		buffer[1] = 45;
		angle = -angle;
	}

	buffer[2] = (angle >> 8) & 255;
	buffer[3] = angle & 255;

	int val = write_s(fd, buffer, 4);

	return val;
}
