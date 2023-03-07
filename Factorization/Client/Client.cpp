// Client side C program
#include <pthread.h>
#include "ConnectionHandler.h"

/*char shared_buffer[BUFF_MAX] = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct thread_data {
    int tid;
    char* data;
};*/

void createSocket(char* data) {  
    int valread;
    char buff[BUFF_MAX] = { 0 };
    //struct thread_data* td = (struct thread_data*)thread_arg;
    
    SocketHandler* sock = newSocketHandler();
    sock->initSocket(sock);
    
    //printf("   $ From Thread(%d):\n", data);
    printf("   -- To Server: %s\n", data);
    sock->sendMessage(sock, data);
    
    do {
        valread = recvMessage(sock, buff);
    } while (valread <= 0);

    //printf("   $ From Thread(%d):\n", dat);
    printf("   -- From Server: Factorial(%s) = %s\n", data, buff);

    sock->closeSocket(sock);
}

int main(int argc, char* argv[])
{
    if (argc > 11 || argc == 1) {
        puts("## Number of arguments invalid/ Min args = 1, Max args = 10");
        exit(EXIT_FAILURE);
    }
    else {
        //pthread_t threads[argc - 1];
        //struct thread_data td[argc - 1];

        for (int i = 0; i < argc - 1; i++) {
            createSocket(argv[i + 1]);
            /*td[i].tid = i;
            td[i].data = argv[i + 1];

            if (pthread_create(&threads[i], NULL, createSocket, &td[i])) {
                perror("## Thread creation failed...");
            }*/
        }
    }

    return 0;
}