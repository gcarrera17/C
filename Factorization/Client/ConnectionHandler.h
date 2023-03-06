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

typedef struct Socket_Handler {
	int sockfd, connfd;
	char buff[BUFF_MAX];
	struct sockaddr_in servaddr;

	void  (*initSocket)(Socket_Handler* self);
	void  (*closeSocket)(Socket_Handler* self);
	void  (*sendMessage)(Socket_Handler* self, char* msg);
	char* (*recvMessage)(Socket_Handler* self);
}SocketHandler;

SocketHandler* newSocketHandler();
void  initSocket(SocketHandler* sh);
void  closeSocket(SocketHandler* sh);
void  sendMessage(SocketHandler* sh, char* msg);
char* recvMessage(SocketHandler* sh);