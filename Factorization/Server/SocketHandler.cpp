// CPP file to handle Server socket connections
#include "SocketHandler.h"

SocketHandler* newSocketHandler() {
    SocketHandler* sh = (SocketHandler*)malloc(sizeof(SocketHandler));
    sh->initSocket = initSocket;
    sh->closeSocket = closeSocket;
    sh->handleConnection = handleConnection;
    sh->sendMessage = sendMessage;
    sh->recvMessage = recvMessage;
    sh->waitForConnections = waitForConnections;
}

void  initSocket(SocketHandler* sh) {
    int opt = TRUE;

    // Creating Socket file descriptor and verification
    if ((sh->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        writeError("## Socket creation failed...");
        exit(EXIT_FAILURE);
    }
    else {
        writeLog("## Socket succesfully created...");
    }

    // Set Socket options and verification
    if (setsockopt(sh->sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        writeError("## Setting socket options failed...");
        exit(EXIT_FAILURE);
    }
    else {
        writeLog("## Socket options succesfully set...");
    }

    // Assing IP, PORT
    sh->servaddr.sin_family = AF_INET;
    sh->servaddr.sin_addr.s_addr = INADDR_ANY;
    sh->servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sh->sockfd, (SA*)&sh->servaddr, sizeof(sh->servaddr))) != 0) {
        writeError("## Socket bind failed...");
        exit(EXIT_FAILURE);
    }
    else {
        writeLog("## Socket succesfully binded...");
    }

    // Now Server is ready to listen and verification
    if ((listen(sh->sockfd, 5)) != 0) {
        writeError("## Listen failed...");
        exit(EXIT_FAILURE);
    }
    else {
        writeLog("## Server listening...");
    }

    sh->waitForConnections(sh);
}

void  waitForConnections(SocketHandler* sh) {
    int addrlen = sizeof(sh->servaddr);

    writeLog("## Waiting for connections...");

    while (TRUE) {
        // Wait for activity in the socket
        if ((sh->connfd = accept(sh->sockfd, (SA*)&sh->servaddr, (socklen_t*)&addrlen)) < 0) {
            writeError("## Server accept failed...");
            continue;
        }
        else {
            writeLog("## New connection...\n   socket id: %d (ip %s, port %d)", sh->connfd, inet_ntoa(sh->servaddr.sin_addr), ntohs(sh->servaddr.sin_port));
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handleConnection, sh) < 0) {
            writeError("## Thread creation failed...");
            continue;
        }

        pthread_detach(thread_id);
    }
}

void* handleConnection(void* sock) {
    int valread;
    SocketHandler* sh = (SocketHandler*)sock;

    while (TRUE) {
        char msg[BUFF_MAX] = { 0 };

        // Read the message from client and print it
        if ((valread = sh->recvMessage(sh, msg)) == 0) {
            writeLog("## Client disconnected...\n   socket id: %d (ip: %s, port: %d)", sh->connfd, inet_ntoa(sh->servaddr.sin_addr), ntohs(sh->servaddr.sin_port));
            close(sh->connfd);
            break;
        }
        else {
            writeLog("## New message from Client(%d): %s", sh->connfd, msg);

            writeLog("   $ Calculation factorial...");
            int res = factorial(atol(msg));
            writeLog("   $ Factorial(%s): %d", msg, res);
            
            sprintf(msg, "%d", res);
            writeLog("   -- To Client(%d): %s", sh->connfd, msg);
            sh->sendMessage(sh, msg);
        }
    }
}

void  closeSocket(SocketHandler* sh) {
    writeLog("## Closing Master socket...");
    
    // Closing the connected socket
    close(sh->sockfd);
}

void  sendMessage(SocketHandler* sh, char* msg) {
    write(sh->connfd, msg, sizeof(msg));
}

int   recvMessage(SocketHandler* sh, char* msg) {
    int valread;
    
    valread = read(sh->connfd, msg, sizeof(msg));
    
    return valread;
}