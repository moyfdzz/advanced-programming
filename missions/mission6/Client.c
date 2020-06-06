#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/inotify.h>
#include <limits.h>
#include <errno.h>

#define PORT 8080
#define MAX_EVENTS 1024 // Max number of events to process
#define LEN_NAME 1024 // Assuming length of the filename won't exceed 16 bytes
#define EVENT_SIZE ( sizeof (struct inotify_event) ) // Size of one event
#define EVENT_BUF_LEN ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ) ) // Buffer to store data of events

// Function that prints the error received as a parameter and then closes the program.
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

// Function to handle events.
char* handleEvent(int fd) {
    char buffer[EVENT_BUF_LEN];
    int length, i = 0;

    // Read to determine the type of event occured on the directory.
    length = read(fd, buffer, EVENT_BUF_LEN);  

    // Verifies the event received.
    if (length < 0 ) {
        perror("ERROR read.");
    }  

    while (i < length) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];

        if (event->len ) {
            if (event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR) {
		            return("The directory %s was created\n", event->name);  
                }       
                else {
		            return("The file %s was created\n", event->name);
                }
            }
             
            if (event->mask & IN_MODIFY) {
                if (event->mask & IN_ISDIR) { 
		            return("The directory %s was modified\n", event->name);  
                }
                else {
		            return("The file %s was modified\n", event->name);
                }       
            }
             
            if (event->mask & IN_DELETE) {
                if (event->mask & IN_ISDIR) {
                    return("The directory %s was deleted\n", event->name );  
                }
                else {
                    return("The file %s was deleted\n", event->name);
                }
            }  

            i += EVENT_SIZE + event->len;
        }
    }
}

int main(void) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    // Variables for the directories and to handle events.
    int fd;
    int wd;
    char buffer[EVENT_BUF_LEN];

    // Creates socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Verifies the socket.
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    // Sets the hostname to localhost.
    server = gethostbyname("localhost");

    // Verifies the hostname.
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // Assigne IP Address and Port
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    // Verifies the connection to the server.
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting to the server.");
    } else {
	    printf("Connection to the server established successfully.\n");
    }
    
    // Creating the inotify instance to monitor directory.
    fd = inotify_init();

    // Verify the inotify instance.
    if (fd < 0 ) {
        error("ERROR creating inotify instance.");
    }

    // Adds the directory to inotify watch list monitor.
    wd = inotify_add_watch(fd, "./User", IN_CREATE | IN_MODIFY | IN_DELETE);

    if (wd == -1) {
        error("[!] Couldn't add watch to /Directory\n");
    } else {
        printf("Watching: /Directory\n");
    }

    while(1) {
        // Sends message to the server.
        printf("Event: ");
        bzero(buffer,256);
        strcpy(buffer, handleEvent(fd));
        n = write(sockfd,buffer,strlen(buffer));

        // Verifies the message.
        if (n < 0) {
            error("ERROR writing to socket.");
        }
            
        // Erases the data stored in the buffer.
        bzero(buffer,256);

        // Reads message from the server.
        n = read(sockfd,buffer,255);

        // Verifies the message received from the server.
        if (n < 0) {
            error("[!] ERROR reading from socket");
        }

        // Prints the message received from the server.
        printf("%s\n",buffer);
    }

     
    // Removes the directory from the inotify watch list monitor.
    inotify_rm_watch(fd, wd);

    // Closes the inotify instance.
    close(fd);
    
    // Closes the socket to stop the communication with the server.
    close(sockfd);

    return 0;
}