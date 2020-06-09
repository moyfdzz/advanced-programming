#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/inotify.h>
#include <limits.h>

#define PORT 8080
#define MAXLINE 1024
#define MAX_EVENTS 1024 // Max number of events to process
#define LEN_NAME 1024 // Assuming length of the filename won't exceed 16 bytes
#define EVENT_SIZE ( sizeof (struct inotify_event) ) // Size of one event
#define EVENT_BUF_LEN ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME ) ) // Buffer to store data of events

char* NEW_FILE_FLAG = "newFile";
char* DELETE_FILE_FLAG = "deleteFile";
char* END_FLAG = "+++===+++END";

// Sending Methods
int sendMethod(char* method);
int sendFileName(char* fileName);
int sendFile(char* fileName);

// Global Variables
int sockfd;
int n;
struct sockaddr_in serv_addr;

// Function that prints the error received as a parameter and then closes the program.
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

// Function to handle events.
const char* handleEvent(int fd) {
    char buffer[EVENT_BUF_LEN];
    char fileName[255];
    int length, i = 0;

    // Read to determine the type of event occured on the directory.
    length = read(fd, buffer, EVENT_BUF_LEN);  

    // Verifies the event received.
    if (length < 0 ) {
        perror("ERROR read.");
    }  

    while (i < length) {
        char *msg = malloc(sizeof(char) * 255);

        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];

        strcpy(fileName, event->name);

        if (event->len ) {
            if (event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR) {
                    sendMethod(NEW_FILE_FLAG);
                    sendFileName(fileName);
                    sendFile(fileName);

                    strcpy(msg, "The directory ");
                    strcat(msg, event->name);
                    strcat(msg, " was created.\n");
                    return msg;
		            //return("The directory %s was created\n", event->name);  
                }       
                else {
                    sendMethod(NEW_FILE_FLAG);
                    sendFileName(fileName);
                    sendFile(fileName);

                    strcpy(msg, "The file ");
                    strcat(msg, event->name);
                    strcat(msg, " was created.\n");
                    return msg;
		            //return("The file %s was created\n", event->name);
                }
            }
             
            if (event->mask & IN_CLOSE_WRITE) {
                if (event->mask & IN_ISDIR) { 
                    sendMethod(NEW_FILE_FLAG);
                    sendFileName(fileName);
                    sendFile(fileName);
                    
                    strcpy(msg, "The dir ");
                    strcat(msg, event->name);
                    strcat(msg, " was modified.\n");
                    return msg;
		            //return("The directory %s was modified\n", event->name);  
                }
                else {
                    sendMethod(NEW_FILE_FLAG);
                    sendFileName(fileName);
                    sendFile(fileName);

                    strcpy(msg, "The file ");
                    strcat(msg, event->name);
                    strcat(msg, " was modified.\n");
                    return msg;
		            //return("The file %s was modified\n", event->name);
                }       
            }
             
            if (event->mask & IN_DELETE) {
                if (event->mask & IN_ISDIR) {
                    sendMethod(DELETE_FILE_FLAG);
                    sendFileName(fileName);

                    strcpy(msg, "The directory ");
                    strcat(msg, event->name);
                    strcat(msg, " was deleted.\n");
                    return msg;
                    //return("The directory %s was deleted\n", event->name);  
                }
                else {
                    sendMethod(DELETE_FILE_FLAG);
                    sendFileName(fileName);

                    strcpy(msg, "The file ");
                    strcat(msg, event->name);
                    strcat(msg, " was deleted.\n");
                    return msg;
                    //return("The file %s was deleted\n", event->name);
                }
            }  

            i += EVENT_SIZE + event->len;
        }
    }
}

// Send method to server
int sendMethod(char* method){
    char buffer[EVENT_BUF_LEN];
    
    sendto(sockfd, method, strlen(method), 0, (struct sockaddr*)NULL, sizeof(serv_addr));

    // Reads message from the server.
    n = read(sockfd,buffer,255);

    // Verifies the message received from the server.
    if (n < 0) {
        error("ERROR reading from socket");
    }

    // Prints the message received from the server.
    printf("\n%s\n",buffer);

    return 0;
}

// Send filename to server
int sendFileName(char* fileName){
    char buffer[EVENT_BUF_LEN];

    sendto(sockfd, fileName, strlen(fileName), 0, (struct sockaddr*)NULL, sizeof(serv_addr));

    // Reads message from the server.
    n = read(sockfd,buffer,255);

    // Verifies the message received from the server.
    if (n < 0) {
        error("ERROR reading from socket");
    }

    // Prints the message received from the server.
    printf("\n%s\n",buffer);

    return 0;
}

// Send file to server
int sendFile(char* fileName){
    char* buffer = malloc(sizeof(char) * 255);

    FILE * fp;
    char line[256];

    char* path = "./User/";
    size_t len = strlen(path) + strlen(fileName) + 1;
    char* fullPath = malloc(len);

    strcpy(fullPath, path);
    strcat(fullPath, fileName);

    fp = fopen(fullPath, "r");
    free(fullPath);

    while(fgets(line, sizeof(line), fp)) {
        strcpy(buffer, line);
        printf("Sending this: %s\n", buffer);
        sendto(sockfd, buffer, n, 0, (struct sockaddr*)NULL, sizeof(serv_addr));

        // Reads message from the server.
        n = read(sockfd,buffer,255);

        // Verifies the message received from the server.
        if (n < 0) {
            error("ERROR reading from socket");
        }

        // Prints the message received from the server.
        printf("\n%s\n",buffer);
    }

    fclose(fp);

    sendto(sockfd, END_FLAG, strlen(END_FLAG), 0, (struct sockaddr*)NULL, sizeof(serv_addr));
}

int main(void) {
        
        /* Our process ID and Session ID */
        pid_t pid, sid;
        
        /* Fork off the parent process */
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        /* Change the file mode mask */
        umask(0);
                
        /* Open any logs here */        
                
        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }
        
        
        /* Change the current working directory */
        /*if ((chdir("/")) < 0) {
                exit(EXIT_FAILURE);
        }*/
 
        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        
        /* Daemon-specific initialization goes here */
        int portno;
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
    wd = inotify_add_watch(fd, "./User", IN_CREATE | IN_CLOSE_WRITE | IN_DELETE);

    if (wd == -1) {
        error("Couldn't add watch to /User\n");
    } else {
        printf("Watching: /User\n");
    }

        /* The Big Loop */
        while(1) {
        // Sends message to the server.
        bzero(buffer,256);
        strcpy(buffer, handleEvent(fd));

        // Prints the action from the directory being monitored.
        printf("Event: %s\n",buffer);

        // Erases the data stored in the buffer.
        bzero(buffer,256);

        /*

        n = write(sockfd,buffer,strlen(buffer));

        // Prints the action from the directory being monitored.
        printf("%s\n",buffer);

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
            error("ERROR reading from socket");
        }

        // Prints the message received from the server.
        printf("\n%s\n",buffer);

        */
    }

    // Removes the directory from the inotify watch list monitor.
    inotify_rm_watch(fd, wd);

    // Closes the inotify instance.
    close(fd);
    
    // Closes the socket to stop the communication with the server.
    close(sockfd);

   exit(EXIT_SUCCESS);
}