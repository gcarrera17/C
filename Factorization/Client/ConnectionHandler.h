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

typedef struct Client_Socket {
	int sockfd;
	char buff[BUFF_MAX];
	struct sockaddr_in servaddr;

	void  (*initSocket)(Client_Socket* self);
	void  (*closeSocket)(Client_Socket* self);
	void  (*sendMessage)(Client_Socket* self);
	int   (*recvMessage)(Client_Socket* self);
}SocketHandler;

SocketHandler* newSocketHandler();
void  initSocket(SocketHandler* sh);
void  closeSocket(SocketHandler* sh);
void  sendMessage(SocketHandler* sh);
int   recvMessage(SocketHandler* sh);