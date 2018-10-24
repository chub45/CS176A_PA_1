//I copied all of the code from the Socket programming guide in the linux howtos website that was provided from the
//section notes. I was unable to find the author.
//SOURCE: http://www.linuxhowtos.org/data/6/server.c 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n;
    struct sockaddr_in serv_addr, client_addr;
    char buffer[128];

    if (argc < 2) {
       fprintf(stderr,"usage %s port\n", argv[0]);
       exit(0);
    }
    
    portno = atoi(argv[1]);

    //Creates socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0) 
        error("ERROR binding");

    //while loop to keep server running
    while(1)
    {
        //listen for a connection request and create socket
        listen(sockfd, 5);
        socklen_t clientLength = sizeof(client_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientLength);
        if(newsockfd < 0)
            error("Error accepting");

        bzero(buffer, 128);

        //Reads data from socket to buffer
        n = read(newsockfd, buffer, 127);

        //While sum has more than 1 digit, continue to add
        int sum = 11;
        while(sum >= 10)
        {
            int i = 0;
            sum = 0;

            //Iterate each char in buffer to make sure it only contains integers
            for(; i < n - 1; i++)
            {
                if(isalpha(buffer[i]))
                {
                    n = write(newsockfd, "Sorry, cannot compute!\n", 23);
                    close(newsockfd);
                    break;
                }
                else
                {
                    sum += (buffer[i] - '0');
                }
            }

            //flush buffer and put current sum to buffer
            memset(buffer, 0, 128);
            sprintf(buffer, "%d\n", sum);
            n = write(newsockfd, "From Server: ", 13);
            n = write(newsockfd, buffer, strlen(buffer));

            if(n < 0)
            {
                break;
            } 
        }
        close(newsockfd);
    }
    return 0;
}
