// Client side C/C++ program to demostrate Socket
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define MAX 1024

void chat(int connfd) {
    char buff[MAX];

    while (TRUE) {
        // Enter message to Server and send it
        bzero(buff, sizeof(buff));
        printf(" -- To Server: ");
        gets(buff);
        write(connfd, buff, sizeof(buff));
        
        // Read message from Server and print it
        bzero(buff, sizeof(buff));
        read(connfd, buff, sizeof(buff));
        printf(" -- From Server: %s\n", buff);

        // if message contains "Exit" then server exit and chat ended
        if (strncmp("exit", buff, 4) == 0)
            break;
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };

    // Creating client socket file descriptor and verification
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("## Socket creation failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Socket succesfully created...");
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if ((connfd = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) < 0) {
        perror("## Connection with server failed...");
        exit(EXIT_FAILURE);
    }
    else {
        puts("## Connected to server successfully...");
    }

    chat(sockfd);
    puts("## Client exit...");

    // closing the connected socket
    close(sockfd);

    return 0;
}