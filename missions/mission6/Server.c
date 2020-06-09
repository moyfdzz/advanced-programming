// Marcos Leroy Salazar Skinner A01039743
// Moisés Fernández Zárate A01197049
// Santiago Castano Moreno A01193760
// Date: 8/6/2020

// Mission 6
// Parte servidor de misión 6, esta parte del código recibe los cambios del cliente y los aplica en el respaldo del servidor.

#include <stdio.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/inotify.h>
#include <fcntl.h>

#define PORT 8080
#define MAXLINE 1024

#define MAX_EVENTS 1024 // Max number of events to process
#define LEN_NAME 1024 // Assuming length of the filename won't exceed 16 bytes
#define EVENT_SIZE ( sizeof (struct inotify_event) ) // Size of one event
#define EVENT_BUF_LEN ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ) ) // Buffer to store data of events

char *NEW_FILE_FLAG = "newFile";
char *DELETE_FILE_FLAG = "deleteFile";
char *END_FLAG = "+++===+++END";

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
    char buffer[MAXLINE], method[MAXLINE], fileName[MAXLINE];
    struct sockaddr_in serv_addr, cli_addr;
    int n, len;

    FILE * fp;

    // Creates the socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Verifies if a port was provided.
    if (sockfd < 0) {
        error("ERROR opening socket");
        exit(1);
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

    printf("Server oppened succesfully! Ready to listen\n\n");
    
    // Accept the data from client.
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    // Verify the connection with the data from client.
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
    

    while(1) {
        bzero(buffer,256);
        bzero(method,256);
        bzero(fileName,256);

        printf("Ready for next event\n");

        // Method
        n = recvfrom(newsockfd, method, MAXLINE, 0, (struct sockaddr*)&cli_addr, (socklen_t *)&len); // message of method
        method[n] = '\0';
        printf("Method: %s\n", method);
        // Send message to client
        n = write(newsockfd,"I got the method",17);

        // Message verification
        if (n < 0) {
            error("ERROR writing to socket");
        }

        // when method new file, update or new file
        if(strcmp(NEW_FILE_FLAG, method) == 0) {
            bzero(fileName,256);
            // File name
            n = recvfrom(newsockfd, fileName, MAXLINE, 0, (struct sockaddr*)&cli_addr, (socklen_t *)&len); // message of fileName
            fileName[n] = '\0';
            printf("File name: %s\n", fileName);

            n = write(newsockfd,"I got the fileName",19);

            // Message verification
            if (n < 0) {
                error("ERROR writing to socket");
            }

            char* path = "./Server/";
            size_t len = strlen(path) + strlen(fileName) + 1;
            char* fullPath = malloc(len);

            strcpy(fullPath, path);
            strcat(fullPath, fileName);

            fp = fopen(fullPath, "w");
            free(fullPath);

            bzero(buffer,256);
            // Receive file
            while ((n = recvfrom(newsockfd, buffer, MAXLINE, 0, (struct sockaddr*)&cli_addr, (socklen_t *)&len)) > 0) {
                buffer[n] = '\0';

                if(strcmp(END_FLAG, buffer) == 0) { // eof reached
                    break;
                }
                printf("\nFile writing this: %s\n", buffer);
                fprintf(fp, "%s", buffer);

                n = write(newsockfd,"I got the line",15);

                // Message verification
                if (n < 0) {
                    error("ERROR writing to socket");
                }
            
            }

            printf("Reached close\n");
            fclose(fp);
        } else if (strcmp(DELETE_FILE_FLAG, method) == 0) { // when method delete
            printf("Entered delete");
            // File name
            n = recvfrom(newsockfd, fileName, MAXLINE, 0, (struct sockaddr*)&cli_addr, (socklen_t *)&len); // message of fileName
            fileName[n] = '\0';
            printf("File name to delete: %s\n", fileName);

            n = write(newsockfd,"I got the fileName",19);

            // Message verification
            if (n < 0) {
                error("ERROR writing to socket");
            }

            char* path = "./Server/";
            size_t len = strlen(path) + strlen(fileName) + 1;
            char* fullPath = malloc(len);

            strcpy(fullPath, path);
            strcat(fullPath, fileName);

            if(remove(fullPath) == 0)
                printf("Deleted %s sucessfully\n", fullPath);
            else
                printf("Unable to delete %s\n", fullPath);

            free(fullPath);

        }


        /*

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

        */
    }

    // Closes the socket to stop the communication with the client.
    close(newsockfd);
    close(sockfd);

    return 0; 
}