//Server Side TCP 

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    //Instatiating variables for socket
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    char *hello = "Hello from server";
    
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


    while(1)
    {
        //Now we accept every new oncoming conection by provigin it with a separate socket
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        //Now we can read and write stuff between the sockets using read/write function
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");

        //Close socket when finished
        close(new_socket);
    }
    return 0;
}