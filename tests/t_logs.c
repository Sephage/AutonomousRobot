#include "t_logs.h"

int testLogs() {
  const char *logFilePath = "../Logs/TestLogs/t_logsTest.log\0";
  const char *wmessage = "I am a test.\n\0";
  const int wmessageLen = strlen(wmessage);
  Log *logs = NULL;
  FILE *logFile = NULL;
  char *rmessage = (char *)malloc(wmessageLen*sizeof(char));
  int nbOfDirectories;

  /* createLogDirectories already got called in the main Function
    so we can just check the return value instead of checking
    each mkdir, one by one */
  nbOfDirectories = createLogDirectories();
  if(nbOfDirectories == (-3) ){
    printf("createLogDirectories = OK\n");
  }
  else {
    printf("createLogDirectories = NOTOK\n");
    logs = closeLogFile(logs);
    free(rmessage);
    return -1;
  }

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

  logFile = fopen(logFilePath, "r");
  fseek(logFile, -wmessageLen, SEEK_END);
  fread(rmessage, sizeof(char), wmessageLen, logFile);
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
