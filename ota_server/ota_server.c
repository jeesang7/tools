#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h> // <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>


#define MAX         80
#define PORT        8080
#define F_BUF_SIZE  1024


static void send_file(int sockfd, int fd, void *buffer) 
{
    char rbuff[MAX];
    int n;
    off_t m;

    for (;;) {
        bzero(rbuff, MAX);

        read(sockfd, rbuff, sizeof(rbuff));

        printf("%s", rbuff);
        bzero(rbuff, MAX);
        n = 0;

        // read filestream and send file to client
        n = read(fd, buffer, F_BUF_SIZE);
        while(n) {
            if ( n == -1 ) {
                printf("File read error \n");
                exit(0);
            }
            write(sockfd, buffer, F_BUF_SIZE);

            if ( strncmp("exit", rbuff, 4) == 0 ) {
                printf("Server Exit...\n"); 
                break;
            }
        }
    }
}

// Function designed for chat between client and server.
static void chatting(int sockfd)
{
    char buff[MAX];
    int n;

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "exit" then server exit and chat ended.
        if ( strncmp("exit", buff, 4) == 0 ) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main(int argc, char **argv)
{
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, client;
#ifdef OTA
    int fd;
    struct stat fstat;
    char fbuffer[F_BUF_SIZE];
    off_t sz;

    if ( (fd = open(argv[1], O_RDONLY)) == -1 ) {
        printf("file open error \n");
        exit(0);
    } 
    
    if ( stat(argv[1], &fstat) == -1 ) {
        printf("stat error \n");
        exit(0);
    } else
        sz = fstat.st_size;
    
    bzero(&fbuffer, F_BUF_SIZE);
#endif

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;      // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ( (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0 ) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ( (listen(sockfd, 5)) != 0 ) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");

    len = sizeof(client);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    } else
        printf("server acccept the client...\n");

    char dest[INET_ADDRSTRLEN];
    unsigned short client_port;

    if ( inet_ntop(AF_INET, &client.sin_addr, dest, INET_ADDRSTRLEN) == NULL ) {
        printf("inet_ntop error... \n");
        exit(0);
    } else {
        client_port = ntohs(client.sin_port);
        printf("connected @ client : %s:%d \n", dest, client_port);
    }

#if OTA
    send_file(connfd, fd, &fbuffer);
#else
    // Function for chatting between client and server
    chatting(connfd);
#endif

    // After chatting close the socket
    close(sockfd);
}
