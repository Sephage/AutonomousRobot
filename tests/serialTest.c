#include "../include/serial/Serial.h"

int main(){
	int fd = open_s("/dev/ttyACM0");

	uint8_t* buffer = (uint8_t*)malloc(4);

	driveSpeed(fd, 200, buffer);
	sleep(2);
	stop(fd, buffer);
	driveMMS(fd, -1000, buffer);
	turn(fd, 180, buffer);
	turn(fd, -180, buffer);

	int val = read(fd, buffer, 5);

	close_s(fd);

	free(buffer);

	return 0;
}
