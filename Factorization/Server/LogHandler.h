#include <stdio.h>

#define LOG_NAME "./server.log"
#define WRITE_CONSOL 1

void timestamp();
void openLog();
void writeLog(char* msg, ...);
void writeError(char* msg, ...);