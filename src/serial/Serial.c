#include "../../include/serial/Serial.h"

#define DEBUG

int open_s(char *name){

	struct termios toptions ;
	int fd;

	#ifdef DEBUG
		printf("Open serial : %s\n", name) ;
	#endif

	if((fd = open(name, O_RDWR))== -1){
		printf("Error opening %s\n", name);
		return -1;
	}

	#ifdef DEBUG
		printf("wait\n") ;
	#endif

	usleep(300000) ;


	if(tcgetattr(fd, &toptions) == -1){
		printf("Error getting attribut from  %s\n", name);
		return -1;
	}

	cfsetispeed(&toptions, B115200) ;
	cfsetospeed(&toptions, B115200) ;
	toptions.c_cflag &= ~PARENB ;
	toptions.c_cflag &= ~CSTOPB ;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8 ;

	toptions.c_cflag &= ~CRTSCTS;

	if(tcsetattr(fd, TCSANOW, &toptions) == -1){
		printf("Error setting attribut to %s\n", name);
		return -1;
	}

	usleep(300000);

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
		printf("Envoie de %c à l'arduino %d\n", buffer, fd);
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
