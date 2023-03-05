// Server side C/C++ program to demostrate Socket
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define MAX 1024

void chat(int connfd) {
    char buff[MAX];

    while (TRUE) {
        // Read the message from client and print it
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        printf(" -- From Client: %s\n", buff);

        // Enter message to Client and send it
        bzero(buff, MAX);
        printf(" -- To Client: ");
        gets(buff);
        write(connfd, buff, sizeof(buff));

        // if message contains "Exit" then server exit and chat ended
        if (strncmp("exit", buff, 4) == 0)
            break;
    }
}

int main()
{
    int sockfd, connfd, addrlen;
    struct sockaddr_in servaddr;
    int opt = TRUE;

    // Creating Socket file descriptor and verification
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("## Socket creation failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket succesfully created...");
    }

    // Set Socket options and verification
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("## Setting socket options failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket options succesfully set...");
    }

    // Assing IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        perror("## Socket bind failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket succesfully binded...");
    }

    // Now Server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        puts("## Listen failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Server listening...");
    }

    addrlen = sizeof(servaddr);
    puts("\nWaiting for connections...");

    // Wait for activity in the socket
    if ((connfd = accept(sockfd, (struct sockaddr*)&servaddr, (socklen_t*)&addrlen)) < 0) {
        perror("## Server accept failed...");
        exit(EXIT_FAILURE);
    }
    else {
        printf("## New connection...\n socket id: %d (ip %s, port %d)\n", connfd, inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
    }

    chat(connfd);
    puts("## Server exit...");

    // Closing the connected socket
    close(sockfd);

    return 0;
}