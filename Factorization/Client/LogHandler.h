#include <stdio.h>

#define LOG_NAME "./client.log"

void timestamp();
void openLog();
void writeLog(char* msg, ...);
void writeError(char* msg, ...);