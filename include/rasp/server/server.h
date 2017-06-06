#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#ifndef SERVER_H
#define SERVER_H

#define PORT 9930 // Port the server is listening to, waiting for a client to connect.

#define BUF_SIZE_SEND 4 // size of message to send to the client.
#define BUF_SIZE_RCV 4 // size of message received from the client.
#define BUF_SIZE_DATA 10 // size of the data message received from the client.
#define NUMBER_OF_TRIES 10 // number of times we try to communicate with the client. Sort of a Time To Live.

typedef struct {
	struct sockaddr_in si_me, si_other;
  int osckt, sckt;
  socklen_t slen;
}Server;

int initialiseServer(Server *server);
/*
	Sends the "End" or "Rcd" messages to client after a received message and its treatment.
*/
void sendEndMsgToClient(Server server, char* msg);

/*
		Sends specially formated Data to the client.
*/
void sendDataToClient(Server server, char* data);

char* receiveFromClient(Server server);

int* receiveAngleFromClient(Server server);

int closeServer(Server *server);

#endif
