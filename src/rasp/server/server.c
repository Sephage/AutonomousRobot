#include "../../../include/rasp/server/server.h"

int initialiseServer(Server *server) {

	server->slen = sizeof(struct sockaddr_in);

	//Create socket
	server->osckt = socket(AF_INET , SOCK_STREAM , 0);
	if (server->osckt == -1) {
			perror("Socket creation error.\n");
			return -1;
	}

	//Prepare the sockaddr_in structure
	server->si_me.sin_family = AF_INET;
	server->si_me.sin_addr.s_addr = INADDR_ANY;
	server->si_me.sin_port = htons(PORT);

	//Bind
	if( bind(server->osckt,(struct sockaddr *)&server->si_me , sizeof(server->si_me)) < 0) {
			perror("Error when binding");
			close(server->osckt);
			return -2;
	}

	//Listen
	listen(server->osckt , 3);

	puts("Waiting for incoming connexionToServer...");

	//accept connection from an incoming client
	server->sckt = accept(server->osckt, (struct sockaddr *)&server->si_other, &server->slen);

	if (server->sckt < 0) {
			perror("Connexion accept failed.");
			close(server->osckt);
			return -3;
	}
	puts("Connexion made");

	return 0;
}

void sendEndMsgToClient(Server server, char* msg) {
	send(server.sckt, msg, BUF_SIZE_SEND, 0);
}

void sendDataToClient(Server server, char* data) {
	send(server.sckt, data, BUF_SIZE_DATA, 0);
}

char* receiveFromClient(Server server) {
	char *message =  (char *)malloc(BUF_SIZE_RCV*sizeof(char));

	do {
		if (recv(server.sckt, message, BUF_SIZE_RCV, 0) == -1) {
			fprintf(stderr, "recvfrom() error.\n");
			close(server.sckt);
		}
	}while((strcmp(message, "Lea") != 0) && (strcmp(message, "Aut") != 0) && (strcmp(message, "Stp") != 0) );

	return message;
}

int closeServer(Server *server) {
	int ret = 0;

	ret = close(server->sckt);
	ret = ret + close(server->osckt);

	return ret;
}
