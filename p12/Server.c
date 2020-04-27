//
// Author: Moisés Fernández
// ID: A01197049
// Date: 17/04/2020
//
// A simple server in the internet domain using TCP.
// The port number is passed as an argument.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

// Used to show an error and prints a message received as a parameter.
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Principal function of the program.
int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Verifies if a port was provided.
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Verifies the socket.
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    // Sets the ports with the input received from the user.
    portno = atoi(argv[1]);

    // Assigns the port and the ip address.
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bings the socket that was created with the user's input.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    // The server is ready to listen.
    listen(sockfd,5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    // Verifies the connection.
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
        
    bzero(buffer,256);

    // To receive the message.
    n = read(newsockfd,buffer,255);

    // Verifies the message received.
    if (n < 0) {
        error("ERROR reading from socket");
    }

    printf("Here is the message: %s\n",buffer);

    n = write(newsockfd,"I got your message",18);

    if (n < 0) {
        error("ERROR writing to socket");
    }

    close(newsockfd);
    close(sockfd);

    return 0; 
}