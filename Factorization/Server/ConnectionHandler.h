// Header file to handle Server socket connections
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define BUFF_MAX 1024
#define SA struct sockaddr

void* handleConnection(void* connfd);
void startConnection(void);
