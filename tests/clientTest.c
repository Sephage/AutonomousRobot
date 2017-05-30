#include "../include/controllerComputer/client.h"

int main () {
  Client client;
  char message[] = "Lea\0";

	connexionToServer(&client);

	sendToServer(client, message);
	printf("Sent message 1 to server.\n");
  strcpy(message, "Aut");
  sendToServer(client, message);
	printf("Sent message 2 to server.\n");
  strcpy(message, "Stp");
  sendToServer(client, message);
	printf("Sent message 3 to server.\n");

	deconnexionFromServer(&client);

	return 0;
}
