#include "../include/serial/Serial.h"

int main(){
	int fd = open_s("/dev/ttyUSB0");
	sleep(1);

	uint8_t* buffer = (uint8_t*)malloc(1);
	buffer[0] = 128;

	write_s(fd, buffer, 1);

	sleep(3);

	buffer[0] = 131;

	write_s(fd, buffer, 1);

	sleep(5);

	/*buffer[0] = 143;

	write_s(fd, buffer, 1);

	sleep(3);*/

	uint8_t* buffer2 = (uint8_t*)malloc(5);

	buffer2[0] = 137;
	buffer2[1] = 0;
	buffer2[2] = 255;
	buffer2[3] = 0;
	buffer2[4] = 255;

	write_s(fd, buffer2, 5);

	close_s(fd);

	free(buffer);
	free(buffer2);

	return 0;

}
