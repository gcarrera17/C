#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include "LogHandler.h"

FILE* fl;

void timestamp() {
	char date[20];
	struct timeval tv;

	// Print the timestamp
	gettimeofday(&tv, NULL);
	strftime(date, sizeof(date) / sizeof(*date), "%Y-%m-%d_%H:%M:%S", gmtime(&tv.tv_sec));
	fprintf(fl, "[%s.%03d]: ", date, tv.tv_usec / 1000);

	if(WRITE_CONSOL)
		printf("[%s.%03d]: ", date, tv.tv_usec / 1000);
}

void openLog() {
	fl = fopen(LOG_NAME, "a");

	fseek(fl, 0, SEEK_END);
	int size = ftell(fl);

	if (size == 0) {
		fputs("****************************** SERVER LOG ******************************", fl);
	}

	if(WRITE_CONSOL)
		puts("****************************** SERVER LOG ******************************");
}

void writeLog(char* fmt, ...) {
	va_list args;
	
	va_start(args, fmt);
	timestamp();
	vfprintf(fl, fmt, args);
	fprintf(fl, "\n");
	va_end(args);

	if (WRITE_CONSOL) {
		va_start(args, fmt);
		timestamp();
		vprintf(fmt, args);
		printf("\n");
		va_end(args);
	}
}

void writeError(char* fmt, ...) {
	va_list args;
	
	va_start(args, fmt);
	timestamp();
	fprintf(fl, "Error - ");
	vfprintf(fl, fmt, args);
	fprintf(fl, "\n");
	va_end(args);

	if (WRITE_CONSOL) {
		va_start(args, fmt);
		timestamp();
		printf("Error - ");
		vprintf(fmt, args);
		printf("\n");
		va_end(args);
	}
}