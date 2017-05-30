#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

/* default value/easy to change variables */
#define IP_SERV "192.168.42.11" // IP of the server we want to connect to.
#define PORT 9930 // Port the server is listening to, waiting for a client to connect.

#define BUF_SIZE_SEND 4 // size of message to send to the server in order to connect the two.
#define BUF_SIZE_RCV 4 // size of message received from server in order to connect the two.
#define BUF_SIZE_DATA 10 // size of the data message we send to the server.
#define NUMBER_OF_TRIES 10 // number of times we try to communicate with the serveur. Sort of a Time To Live.

typedef struct {
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	int clientSocket;
}Client;

void connexionToServer(Client *client);
void sendToServer(Client client, char* message);
char* receiveDataFromServer(Client client);
int deconnexionFromServer(Client *client);
