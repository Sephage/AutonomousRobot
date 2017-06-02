#include "../include/serial/Serial.h"

int main(){
	int fd = open_s();
	int val=0;

	uint8_t* buffer = (uint8_t*)malloc(4);
	uint8_t* buffer2 = (uint8_t*)calloc(10,1);
	printf("Lu : %d %d %d %d result  %d\n", buffer2[0], buffer2[1], buffer2[2], buffer2[3], val);

	driveSpeed(fd, 200, buffer);
	sleep(2);
	stop(fd, buffer);
	driveMMS(fd, -1000, buffer);
	sleep(2);
	turn(fd, 180, buffer);
	sleep(3);
	turn(fd, -180, buffer);
	sleep(2);
	int angle = askAngle(fd, buffer, buffer2);
	printf("angle =  %d \n", angle);

	close_s(fd);

	free(buffer);

	return 0;
}
