#include "../include/serial/Serial.h"
#include "../include/rasp/imageProcessing/imageUtility.h"

int main(){
	int fd = open_s();
	int val=0;

	/*uint8_t* buffer = (uint8_t*)malloc(4);
	turnServo(fd,90,buffer);
	driveSpeed(fd, 200, buffer);
	sleep(2);
	stop(fd, buffer);
	driveMMS(fd, -1000, buffer);
	turnServo(fd,0,buffer);
	sleep(2);
	turn(fd, 180, buffer);
	sleep(3);
	turn(fd, -180, buffer);
	sleep(2);
	turnServo(fd,180,buffer);
	int angle = askAngle(fd, buffer);
	printf("angle =  %d \n", angle);*/

	captureAll(fd, 0);

	close_s(fd);

	//free(buffer);

	return 0;
}
