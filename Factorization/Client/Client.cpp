// Client side C program
#include <pthread.h>

#include "SocketHandler.h"
#include "LogHandler.h"

void createSocket(char* data) {  
    int valread;
    char buff[BUFF_MAX] = { 0 };
    
    SocketHandler* sock = newSocketHandler();
    sock->initSocket(sock);
    
    writeLog("   -- To Server: %s", data);
    sock->sendMessage(sock, data);
    
    do {
        valread = recvMessage(sock, buff);
    } while (valread <= 0);

    writeLog("   -- From Server: Factorial(%s) = %s", data, buff);

    sock->closeSocket(sock);
}

int main(int argc, char* argv[])
{
    openLog();
    if (argc > 11 || argc == 1) {
        writeError("## Number of arguments invalid/ Min args = 1, Max args = 10");
        exit(EXIT_FAILURE);
    }
    else {
        for (int i = 0; i < argc - 1; i++) {
            createSocket(argv[i + 1]);
        }
    }

    return 0;
}