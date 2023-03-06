// CPP file to handle Server socket connections
#include "ConnectionHandler.h"

void* handleConnection(void* connfd) {
    char buff[BUFF_MAX];
    int valread;
    int sock = *(int*)connfd;

    while (TRUE) {
        // Read the message from client and print it
        bzero(buff, BUFF_MAX);
        if ((valread = read(sock, buff, sizeof(buff))) == 0) {
            printf("## Client disconnected...\n socket id: %d\n", sock);
            close(sock);
            break;
        }
        else {
            printf("## New message from Client(%d): %s\n", sock, buff);
            strcat(buff, "!!!");
            printf("  -- To Client(%d): %s\n", sock, buff);
            write(sock, buff, sizeof(buff));
        }
    }
}

SocketHandler* newSocketHandler() {
    SocketHandler* sh = (SocketHandler*)malloc(sizeof(SocketHandler));
    sh->initSocket = initSocket;
    sh->closeSocket = closeSocket;
    sh->sendMessage = sendMessage;
    sh->recvMessage = recvMessage;
    sh->waitForConnections = waitForConnections;
}

void  initSocket(SocketHandler* sh) {
    int opt = TRUE;

    // Creating Socket file descriptor and verification
    if ((sh->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("## Socket creation failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket succesfully created...");
    }

    // Set Socket options and verification
    if (setsockopt(sh->sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("## Setting socket options failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket options succesfully set...");
    }

    // Assing IP, PORT
    sh->servaddr.sin_family = AF_INET;
    sh->servaddr.sin_addr.s_addr = INADDR_ANY;
    sh->servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sh->sockfd, (SA*)&sh->servaddr, sizeof(sh->servaddr))) != 0) {
        perror("## Socket bind failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket succesfully binded...");
    }

    // Now Server is ready to listen and verification
    if ((listen(sh->sockfd, 5)) != 0) {
        puts("## Listen failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Server listening...");
    }

    sh->waitForConnections(sh);
}

void  waitForConnections(SocketHandler* sh) {
    int addrlen = sizeof(sh->servaddr);

    puts("Waiting for connections...");

    while (TRUE) {
        // Wait for activity in the socket
        if ((sh->connfd = accept(sh->sockfd, (SA*)&sh->servaddr, (socklen_t*)&addrlen)) < 0) {
            perror("## Server accept failed...");
            continue;
        }
        else {
            printf("## New connection...\n socket id: %d (ip %s, port %d)\n", sh->connfd, inet_ntoa(sh->servaddr.sin_addr), ntohs(sh->servaddr.sin_port));
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handleConnection, &sh->connfd) < 0) {
            perror("## Thread creation failed...");
            continue;
        }

        pthread_detach(thread_id);
    }
}

void  closeSocket(SocketHandler* sh) {
    puts("## Closing Master socket...");
    
    // Closing the connected socket
    close(sh->sockfd);
}

void  sendMessage(SocketHandler* sh, char* msg) {
    write(sh->sockfd, msg, sizeof(msg));
}

char* recvMessage(SocketHandler* sh) {
    bzero(sh->buff, sizeof(sh->buff));
    read(sh->connfd, sh->buff, sizeof(sh->buff));
    return sh->buff;
}