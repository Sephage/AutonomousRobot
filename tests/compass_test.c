#include "../include/serial/Serial.h"

int main(){

	char* buffer = (char*)malloc(4 * sizeof(char));
	int fd = open_s();
	int i;

	for(i = 0 ; i < 36 ; i++){
		turn(fd, 10, buffer);
		usleep(1000000);
	}
//turn(fd, 2, buffer);
	free(buffer);
	close_s(fd);
	return 0;
}
