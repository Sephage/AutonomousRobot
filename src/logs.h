#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* All logs must be located in "../Logs" folder
  And separated into sub-folders depending
  on their type */

typedef struct Log {
  FILE *logFile;
  char *logFilePath;
}Log;

int createLogDirectories();
Log* initialiseLogFile(const char *path);
void writeLogFile(Log *log, const char *message);
Log* closeLogFile(Log *log);
