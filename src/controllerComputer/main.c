#include "../../include/controllerComputer/client.h"
int main () {


  Client client;
  int loop = 1;
  int angle = 0;
  char *cont =  (char *)malloc(sizeof(char));
  char msg[] = "Lea\0";
  char *data;

  connexionToServer(&client);

  /* Leaning mode */
  while(loop) {
    sendToServer(client, msg);
    receiveFromServer(client);
    printf("Continue learning? (Y/n)\n");
    scanf("%c", cont);
    if(strcmp((const char *)cont, "n") == 0 || strcmp((const char *)cont, "N") == 0) {
      loop = 0;
      sendToServer(client, "Stp");
    }
  }

  loop = 1;

  /* Autonomous Mode */
  strcpy(msg, "Aut");
  sendToServer(client, msg);
  while(loop) {
//    data = receiveDataFromServer(Client client);
    receiveFromServer(client);
  }

  deconnexionFromServer(&client);

  return 0;
}
