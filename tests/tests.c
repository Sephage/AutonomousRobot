#include <stdio.h>
#include <stdlib.h>

#include "t_functions.h"

int main(int argc, char *argv[]) {
  Log *logs;
  char return_Code[256];
  int success = 1;
  int resultT_logs, resultT_Server;

  createLogDirectories();
  logs = initialiseLogFile("../Logs/TestLogs/tests.log");

  // Start of tests

  resultT_logs = testLogs();
  printf("Test Log exit code : %d.\n", resultT_logs);
  if(resultT_logs == 0) {
    writeLogFile(logs, "[SUCCESS] Function testLogs() returned with exit code: 0.\n");
  }
  else {
    sprintf(return_Code, "%d", resultT_logs);

    writeLogFile(logs, "[ERROR] Function testLogs() returned with exit code: ");
    writeLogFile(logs, (const char *)return_Code);
    writeLogFile(logs, ".\n");
    success = 0;
  }

  resultT_Server = testServer();
  printf("Test Server exit code : %d.\n", resultT_Server);
  if(resultT_Server == 0) {
    writeLogFile(logs, "[SUCCESS] Function testServer() returned with exit code: 0.\n");
  }
  else {
    sprintf(return_Code, "%d", resultT_Server);

    writeLogFile(logs, "[ERROR] Function testServer() returned with exit code: ");
    writeLogFile(logs, (const char *)return_Code);
    writeLogFile(logs, ".\n");
    success = 0;
  }

  // End of tests and conclusion

  if(success) {
    writeLogFile(logs, "[SUCCESS] End of tests, no error detected.\n");
  }
  else {
    writeLogFile(logs, "[ERROR] End of tests, at least one error has occured.\n");
  }

  logs = closeLogFile(logs);
  return 0;
}
