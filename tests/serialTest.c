#include "../include/serial/Serial.h"
#include "../include/rasp/imageProcessing/imageUtility.h"

int main(){
	int fd = open_s();
	int val=0;

	uint8_t* buffer = (uint8_t*)malloc(4);
	//turnServo(fd,90,buffer);
	//driveSpeed(fd, 200, buffer);
	//sleep(2);
	//stop(fd, buffer);
	//driveMMS(fd, 3000, buffer);
	//turnServo(fd,0,buffer);
	//sleep(5);
	//driveMMS(fd, -3000, buffer);
	//turn(fd, 180, buffer);
	//sleep(3);
	//turn(fd, -180, buffer);
	//sleep(2);
	//turnServo(fd,180,buffer);
	//int angle = askAngle(fd, buffer);
	//printf("angle =  %d \n", angle);
	turn(fd, 180, buffer);
	printf("turn \n");

	turn(fd, 0, buffer);
	printf("turn \n");

	turn(fd, 90, buffer);
	printf("turn \n");
	//sleep(6);
	turn(fd, 180, buffer);
	printf("turn \n");

	turn(fd, 270, buffer);
	printf("turn \n");
	turn(fd, 360, buffer);
	printf("turn \n");

	turn(fd, 325, buffer);
	printf("turn \n");

	turn(fd, 45, buffer);
	printf("turn \n");
	turn(fd, 360, buffer);
	printf("turn \n");
	turn(fd, 90, buffer);
	printf("turn \n");
	close_s(fd);

	free(buffer);

	return 0;
}
