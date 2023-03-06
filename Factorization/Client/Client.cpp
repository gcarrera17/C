// Client side C program
#include "ConnectionHandler.h"

int main()
{
    SocketHandler* sock = newSocketHandler();
    sock->initSocket(sock);

    while (TRUE) {
        char buff[BUFF_MAX];
        bzero(buff, sizeof(buff));
        printf(" -- To Server: ");
        gets(buff);

        // if message contains "Exit" then server exit and chat ended
        if (strncmp("exit", buff, 4) == 0)
            break;

        strcpy(sock->buff, buff);

        sock->sendMessage(sock);
        sock->recvMessage(sock);

        printf(" -- From Server: %s\n", sock->buff);
    }

    sock->closeSocket(sock);

    return 0;
}