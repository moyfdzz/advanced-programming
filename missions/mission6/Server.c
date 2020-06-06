#include <stdio.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/inotify.h>

#define PORT 8080
#define MAX_EVENTS 1024 // Max number of events to process
#define LEN_NAME 1024 // Assuming length of the filename won't exceed 16 bytes
#define EVENT_SIZE ( sizeof (struct inotify_event) ) // Size of one event
#define EVENT_BUF_LEN ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ) ) // Buffer to store data of events

// Function that prints the error received as a parameter and then closes the program.
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Principal function of the program.
int main()
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[EVENT_BUF_LEN];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Creates the socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Verifies if a port was provided.
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    // Erase data from serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    // Assign IP Address and Port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Binding the created socket
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }

    // The server is ready to listen.
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    // Accept the data from client.
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    // Verify the connection with the data from client.
    if (newsockfd < 0) {
        error("ERROR on accept");
    }

    while(1) {
        bzero(buffer,256);

        // Read message from client and store it in the buffer.
        n = read(newsockfd,buffer,255);
        
        // Verifies the message received.
        if (n < 0) {
        error("ERROR reading from socket");
        }
        
        // Prints the message received.
        printf("Here is the message: %s\n",buffer);

        // Send message to client
        n = write(newsockfd,"I got your message",18);

        // Message verification
        if (n < 0) {
            error("ERROR writing to socket");
        }
    }

    // Closes the socket to stop the communication with the client.
    close(newsockfd);
    close(sockfd);

    return 0; 
}