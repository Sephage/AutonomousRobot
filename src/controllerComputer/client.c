#include "../../include/controllerComputer/client.h"

void connexionToServer(Client *client) {
	int ret;

	//Create socket
	client->clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (client->clientSocket == -1) {
			perror("ERROR : Could not create socket");
			exit(1);
	}

	client->serverAddr.sin_addr.s_addr = inet_addr(IP_SERV);
	client->serverAddr.sin_family = AF_INET;
	client->serverAddr.sin_port = htons(PORT);

	//Connect to remote server
	ret = connect(client->clientSocket , (struct sockaddr *)&client->serverAddr , sizeof(client->serverAddr));
	if (ret < 0) {
			perror("ERROR : can't connect to the server");
			exit(1);
	}
	puts("Connected to server.\n");

}

void sendToServer(Client client, char message[4]) {

	/* Messages qu'il faut envoyer :
			- Lea : Indique au robot de se mettre en mode apprentissage, puis d'apprendre la place où il est posé.
			- Aut : Indique au robot de passer en mode autonome.
			- Stp : Indique au robot lorsqu'une phase est terminée ou à la fin.
	*/

	/* Messages de confirmation qu'il est possible de recevoir :
			- Rcd : a bien reçu le message (changement de mode, etc.).
			- End : A terminé une phase/calcul/autre.
	*/

	send(client.clientSocket, message, BUF_SIZE_SEND, 0);
}

char* receiveDataFromServer(Client client) {
	char * data = (char *)malloc(BUF_SIZE_DATA);
	recv(client.clientSocket, data, BUF_SIZE_DATA, 0);


	return data;
}

int deconnexionFromServer(Client *client) {
	return close(client->clientSocket);
}
