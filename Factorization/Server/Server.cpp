// Server side C/C++ program to demostrate Socket
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define TRUE 1
#define FALSE 0
#define MAX 1024
#define SA struct sockaddr

void* handleConnection(void* connfd) {
    char buff[MAX];
    int valread;
    int sock = *(int*)connfd;

    while (TRUE) {
        // Read the message from client and print it
        bzero(buff, MAX);
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

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;
    int opt = TRUE;
    int addrlen = sizeof(servaddr);

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
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
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

    puts("\nWaiting for connections...");

    while (TRUE) {
        // Wait for activity in the socket
        if ((connfd = accept(sockfd, (SA*)&servaddr, (socklen_t*)&addrlen)) < 0) {
            perror("## Server accept failed...");
            continue;
        }
        else {
            printf("## New connection...\n socket id: %d (ip %s, port %d)\n", connfd, inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));
        }

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handleConnection, &connfd) < 0) {
            perror("## Thread creation failed...");
            continue;
        }

        pthread_detach(thread_id);
    }

    // Closing the connected socket
    close(sockfd);

    return 0;
}