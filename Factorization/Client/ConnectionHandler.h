// Header file to handle Client socket connections
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define BUFF_MAX 1024
#define SA struct sockaddr

void handleConnection(int connfd);
void startConnection(void);