#include "t_functions.h"

int testLogs() {
  const char *logFilePath = "../Logs/TestLogs/t_logsTest.log";
  const char *wmessage = "I am a test.\n";
  const int wmessageLen = strlen(wmessage);
  Log *logs = NULL;
  FILE *logFile = NULL;
  char *rmessage = (char *)malloc(wmessageLen*sizeof(char));
//  int nbOfCreateErrors;

  /* createLogDirectories already got called in the main Function
    so we can just check the return value instead of checking
    each mkdir, one by one */
/*  nbOfCreateErrors = createLogDirectories();
  if(nbOfCreateErrors == (-3) ){
    printf("createLogDirectories = OK\n");
  }
  else {
    printf("createLogDirectories = NOTOK\n");
    logs = closeLogFile(logs);
    free(rmessage);
    return -1;
  }*/

  logs = initialiseLogFile(logFilePath);
  if((strcmp(logs->logFilePath, logFilePath) == 0)
      && (logs->logFile != NULL))
  {
    printf("initialiseLogs = OK\n");
  }
  else {
    printf("initialiseLogs = NOTOK\n");
    logs = closeLogFile(logs);
    free(rmessage);
    return -2;
  }

  writeLogFile(logs, wmessage);
  logs = closeLogFile(logs);

  logFile = fopen(logFilePath, "rb");
  fseek(logFile, -wmessageLen - (53*3), SEEK_END);
  fread(rmessage, sizeof(char), strlen(wmessage), logFile);
  if((strcmp(rmessage, wmessage) == 0)) {
    printf("writeLogFile = OK\n");
  }
  else {
    printf("writeLogFile = NOTOK, read message: '%s', should be: '%s'\n", rmessage, wmessage);
    fclose(logFile);
    free(rmessage);
    return -3;
  }

  if(logs == NULL) {
    printf("closeLogFile = OK\n");
  }
  else {
    printf("closeLogFile = NOTOK\n");
    free(rmessage);
    return -4;
  }

  free(rmessage);

  return 0;
}

int testServer() {
  Server server;
  char sendMsg[] = "End";
  int returnCode = initialiseServer(&server);
  int closeValue;

  if(returnCode != 0) {
    printf("initialiseServer = NOTOK, return Code is %d, should be 0.\n", returnCode);
    return -1;
  }

  char *rmess1 = receiveFromClient(server);
  printf("Received msg 1 from client\n");
//  sendEndMsgToClient(server, sendMsg);
//  printf("Sent msg 1 from client");
  char *rmess2 = receiveFromClient(server);
  printf("Received msg 2 from client\n");
  strcpy(sendMsg, "Rcd");
//  sendEndMsgToClient(server, sendMsg);
//  printf("Sent msg 1 from client");
  char *rmess3 = receiveFromClient(server);
  printf("Received msg 3 from client\n");
  if((strcmp(rmess1, "Lea") == 0) && (strcmp(rmess2, "Aut") == 0) && (strcmp(rmess3, "Stp") == 0)) {
    printf("sendEndMsg and receiveFromClient = OK.\n");
  }
  else {
    printf("sendEndMsg and receiveFromClient = NOTOK. Messages received are %s, %s and %s, should be Lea, Aut, and Stp.\n", rmess1, rmess2, rmess3);
    return -2;
  }

  closeValue = closeServer(&server);
  if(closeValue == 0) {
    printf("closeServer = OK.\n");
  }
  else {
    printf("closeServer = NOTOK. Socket value is %d.\n", server.sckt);
    return -3;
  }

  return 0;
}
