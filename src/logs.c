#include <time.h>
#include "../include/logs.h"

int createLogDirectories() {
  int result = 0;

  result += mkdir("../Logs", 0777);
  result += mkdir("../Logs/TestLogs", 0777);
  result += mkdir("../Logs/RunTimeLogs", 0777);

  return result;
}

Log* initialiseLogFile(const char *path) {
  time_t seconds;
  struct tm now;

  time(&seconds);
  now = *localtime(&seconds);

  Log* log = (Log*)malloc(sizeof(Log*));
  log->logFilePath = (char *)path;
  log->logFile = fopen(log->logFilePath, "a");
  writeLogFile(log, "****************************************************\n\0");
  writeLogFile(log, "*                  New Code Execution              *\n\0");
  writeLogFile(log, "*              Date: \0");
  writeLogFile(log, "HereIsSupposedToBeTheDate\0");
  writeLogFile(log, "     *\n\0");
  writeLogFile(log, "****************************************************\n\0");
  return log;
}

void writeLogFile(Log *log, const char *message) {
  fwrite((char *)message, sizeof(char), strlen(message), log->logFile);
}

Log* closeLogFile(Log *log) {
  fclose(log->logFile);
  free(log);
  return NULL;
}
