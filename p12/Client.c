//
// Author: Moisés Fernández
// ID: A01197049
// Date: 17/04/2020
//
// A simple server in the internet domain using TCP.
// The hostname and port are received as parameters.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// Used to show an error and prints a message received as a parameter.
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

// Principal function of the program.
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    // There was an error, prints the correct usage of the client.
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Verifies the socket.
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);

    // There was an error, prints extra information about the error.
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // There was an error, it couldn't connect to the server.
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));

    // There was an error, coudn't write to socket.
    if (n < 0) {
        error("ERROR writing to socket");
    }

    bzero(buffer,256);
    n = read(sockfd,buffer,255);

    // There was an error, couldn't read from socket.
    if (n < 0) {
        error("ERROR reading from socket");
    }

    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}