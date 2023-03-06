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

typedef struct Server_Socket {
	int sockfd, connfd;
	char buff[BUFF_MAX];
	struct sockaddr_in servaddr;

	void  (*initSocket)(Server_Socket* self);
	void  (*closeSocket)(Server_Socket* self);
	void  (*waitForConnections)(Server_Socket* self);
	void* (*handleConnection)(void* self);
	void  (*sendMessage)(Server_Socket* self);
	int   (*recvMessage)(Server_Socket* self);

	private:
}SocketHandler;

SocketHandler* newSocketHandler();
void  initSocket(SocketHandler* sh);
void  closeSocket(SocketHandler* sh);
void  waitForConnections(SocketHandler* sh);
void* handleConnection(void* sock);
void  sendMessage(SocketHandler* sh);
int   recvMessage(SocketHandler* sh);
