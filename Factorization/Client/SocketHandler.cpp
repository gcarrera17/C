// CPP file to handle Client socket connections
#include "SocketHandler.h"

SocketHandler* newSocketHandler() {
    SocketHandler* sh = (SocketHandler*)malloc(sizeof(SocketHandler));
    sh->initSocket = initSocket;
    sh->closeSocket = closeSocket;
    sh->sendMessage = sendMessage;
    sh->recvMessage = recvMessage;
}

void initSocket(SocketHandler* sh) {
    // Creating client socket file descriptor and verification
    if ((sh->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        writeError("## Socket creation failed...");
        exit(EXIT_FAILURE);
    }
    else {
        writeLog("## Socket succesfully created...");
    }

    sh->servaddr.sin_family = AF_INET;
    sh->servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sh->servaddr.sin_port = htons(PORT);

    if (connect(sh->sockfd, (SA*)&sh->servaddr, sizeof(sh->servaddr)) < 0) {
        writeError("## Connection with server failed...");
        exit(EXIT_FAILURE);
    }
    else {
        writeLog("## Connected to server successfully...");
    }
}

void closeSocket(SocketHandler* sh) {
    writeLog("## Closing connection with server...");
    
    // closing the connected socket
    close(sh->sockfd);
}

void sendMessage(SocketHandler* sh, char* msg) {
    write(sh->sockfd, msg, sizeof(msg));
}

int recvMessage(SocketHandler* sh, char* msg) {
    int valread;

    valread = read(sh->sockfd, msg, sizeof(msg));
    
    return valread;
}