// Server side C program
#include "SocketHandler.h"

int main()
{
    openLog();
    SocketHandler* sock = newSocketHandler();
    sock->initSocket(sock);
    sock->closeSocket(sock);

    return 0;
}