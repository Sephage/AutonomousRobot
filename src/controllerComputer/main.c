#include "client.h"

int main () {

  Client client;
  int loop = 1;
  int angle = 0;
  char cont;
  char msg[] = "Lea\0";
  char * data;

  connexionToServer(&client);

  /* Leaning mode */
  while(loop) {
    sendToServer(client, msg);
    receiveFromServer(client);
    printf("Please notify the angle to turn in order to go towards the goal :\n");
    scanf("%d", angle);
    sendAngleToServer(client, angle);
    printf("Continue learning? (Y/n)\n");
    scanf("%c", cont);
    if(strcmp(cont, "n") == 0 || strcmp(cont, "N") == 0) {
      loop = 0;
    }
  }

  loop = 1;

  /* Autonomous Mode */
  strcpy(msg, "Aut");
  sendToServer(client, msg);
  while(loop) {
//    data = receiveDataFromServer(Client client);
  }

  deconnexionFromServer(&client);

  return 0;
}
