//I copied all of the code from the Socket programming guide in the linux howtos website. I was unable to find the
//author.
//SOURCE: http://www.linuxhowtos.org/data/6/client_udp.c
/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[128];
   
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }

   //create socket
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");
   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);

   //Asking for string input and then sending input to server socket
   printf("Enter a string: ");
   bzero(buffer,128);
   fgets(buffer,127,stdin);

   //Send a message to socket address
   n=sendto(sock,buffer,
            strlen(buffer),0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");

   //Print out from buffer while connection with server is open
   while(n > 0)
   {
        n = recvfrom(sock,buffer,128,0,(struct sockaddr *)&from, &length);
        if (n < 0) break;
        write(1,"From Server: ", 13);
        write(1,buffer,n);
        if(n == 23 || n == 2)
        {
            n = -1;
        }
   }
   close(sock);
   return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
