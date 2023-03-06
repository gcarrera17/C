// Client side C program
#include "ConnectionHandler.h"

void createSocket(char* data) {  
    int valread;
    
    SocketHandler* sock = newSocketHandler();
    sock->initSocket(sock);

    printf("  -- To Server: %s\n", data);
    sock->sendMessage(sock, data);
    
    do {
        valread = recvMessage(sock);
    } while (valread <= 0);

    printf("  -- From Server: Factorial(%s): %s\n", data, sock->buff);

    sock->closeSocket(sock);
}

int main(int argc, char* argv[])
{
    if (argc > 11 || argc == 1) {
        puts("Number of arguments invalid/ Min args = 1, Max args = 10");
        exit(EXIT_FAILURE);
    }
    else {
        for (int i = 1; i < argc; i++) {
            createSocket(argv[i]);
        }
    }

    return 0;
}