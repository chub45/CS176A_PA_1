//I copied all of the code from the Socket programming guide in the linuxhowtos website that was provided from the
//section notes. I was unable to find the author.
//SOURCE: http://www.linuxhowtos.org/data/6/server_udp.c

/* Creates a datagram server.  The port 
   number is passed as an argument.  This
   server runs forever */

#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    //while loop to keep server running
    while(1)
    {
        int sock, length, n;
        socklen_t fromlen;
        struct sockaddr_in server;
        struct sockaddr_in from;
        char buf[128];

        if (argc < 2) {
            fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
        }

        //Creates socket
        sock=socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) error("Opening socket");

        length = sizeof(server);
        bzero(&server,length);
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
        server.sin_port=htons(atoi(argv[1]));
        if (bind(sock,(struct sockaddr *)&server,length)<0) 
            error("binding");
       
        fromlen = sizeof(struct sockaddr_in);

        //Receives message from socket
        n = recvfrom(sock,buf,128,0,(struct sockaddr *)&from,&fromlen);
        
        //Check to see if socket is still open
        if (n > 0)
        {
            //while sum has more than 1 digit, continue to add
            int sum = 11;
            while(sum >= 10)
            {
                int i = 0;
                sum = 0;

                //Iterate each char in buffer to make sure it only contains integers
                for(; i < n - 1; i++)
                {
                    if(isalpha(buf[i]))
                    {
                        n = sendto(sock, "Sorry, cannot compute!\n", 23, 0, (struct sockaddr *)&from, fromlen);
                        close(sock);
                        break;
                    }
                    else
                    {
                        sum += (buf[i] - '0');
                    }
                }

                //flush buffer and put current sum to buffer
                memset(buf, 0, 128);
                sprintf(buf, "%d\n", sum);
                n = sendto(sock,buf,strlen(buf), 0,(struct sockaddr *)&from,fromlen);
                if(n < 0){
                    break;
                }
            }
            close(sock);
        }
    }
    return 0;
 }
