#include "../include/serial/Serial.h"

int main(){
	int fd = open_s("/dev/ttyUSB0");
	sleep(1);

	uint8_t* buffer = (uint8_t*)malloc(1);

	//Start
	buffer[0] = 128;
	int val = write_s(fd, buffer, 1);
	printf("Start = %d\n", val);
	sleep(3);


	buffer[0] = 131;
	val = write_s(fd, buffer, 1);
	printf("Safe mode = %d\n", val);
	sleep(10);

	/*buffer[0] = 143;

	write_s(fd, buffer, 1);

	sleep(3);*/

	uint8_t* buffer2 = (uint8_t*)malloc(5);

	buffer2[0] = 137;
	buffer2[1] = 255;
	buffer2[2] = 56;
	buffer2[3] = 1;
	buffer2[4] = 244;

	val = write_s(fd, buffer2, 5);
	printf("Move = %d\n", val);
	close_s(fd);

	free(buffer);
	free(buffer2);

	return 0;

}
