//I copied all of the code from the Socket programming guide in the linuxhowtos website. I was unable to find the
//author.
//of the guide.
//SOURCE: http://www.linuxhowtos.org/data/6/client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[128];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    //Converting port chars to integer
    portno = atoi(argv[2]);

    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //Asking for string input and then sending input to server socket
    printf("Enter String: ");
    bzero(buffer,128);
    fgets(buffer,127,stdin);

    //Writes from the buffer to the socket
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,128);

    //Print out from buffer while connection with server is open
    while(n > 0)
    {
        n = read(sockfd,buffer,127);
        if (n < 0) 
            error("ERROR reading from socket");
        write(1, buffer, n);
        if(n == 23 || n == 2)
        {
            n = -1;
        }
    }
    close(sockfd);
    return 0;
}
