//Server Side TCP 

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#define THREAD_NUM 20
#define PORT 8080

struct args {
    int socket;
    char *http;
    int response_len;
    int pthred_num;
};

pthread_t th[THREAD_NUM];


void http_response (char * dest){
    char line[10000];
    char html[100000] = "";
    FILE * fpointer = fopen("index.html", "r");

    while (fgets(line, 255, fpointer)){
        // line[ strcspn(line, "\n" ) ] = '\0';
        strcat(html, line);
    }

    fclose(fpointer);

    strcat(dest,html);
}

void* multithreading_helper(void *input){
        //Now we can read and write stuff between the sockets using read/write function
        int new_socket = ((struct args*)input)->socket;
        char buffer[30000] = {0};
        long valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , ((struct args*)input)->http, ((struct args*)input)->response_len);
        printf("------------------Hello message sent-------------------\n");

        //Close socket when finished
        close(new_socket);
        pthread_join(th[((struct args*)input)->pthred_num],NULL);
}

int main(int argc, char const *argv[])
{
    //Instatiating variables for socket
    int server_fd, new_socket; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    //Change response based on type
    char response [100000] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 100000\n\n ";
    http_response(response);
    
    // Creating socket
    //socket parameters (domain/address family (IP, IPv6 etc), type of service, protcol that is 0 in this case for TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
    //Binding the socket
    //First defining the socket_address (address) struct with the necessary family, port, addr information
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    //The memset() function sets the first count bytes of dest to the value c --> (void *str, int c, size_t n)
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    //This is the binding function that the socket with the necessary parameters
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    //The listens functions makes the socket capable of accepting other connections 
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    struct args *input_data = (struct args *)malloc(sizeof(struct args));


    while(1)
    {
        //Now we accept every new oncoming conection by provigin it with a separate socket
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        printf("no problem till");
        input_data->socket = new_socket;
        input_data->http = response;
        input_data->response_len = strlen(response);
        input_data->pthred_num = i;

        pthread_create(&th[i++], NULL, &multithreading_helper, (void *)input_data);

        // if (i % 2 == 0)
        // {
        //     int j = 0;
        //     while(j <= THREAD_NUM)
        //     {
        //     pthread_join(th[j++],NULL);
        //     }    
        // }

    }
    return 0;
}