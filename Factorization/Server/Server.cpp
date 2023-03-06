// Server side C program
#include "ConnectionHandler.h"

int main()
{
    SocketHandler* sock = newSocketHandler();
    sock->initSocket(sock);
    sock->closeSocket(sock);

    return 0;
}