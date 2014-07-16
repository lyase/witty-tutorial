#include <arpa/inet.h>
#include <cassert> // For assert().
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
using namespace std;

// file from linux magazine hors serie 40
// se compile avec
//gcc web_client1.c -o web
// or g++ webclient.cpp -o build/googlecl

// this programme will connect with tcp/ip to  server
//on port 8000 send http request and read  900 char in reply
//more or less it replaces the following manual command
// curl -vv localhost:8000
// note our reply is
// Transfer-Encoding: chunked
//
// 6
// hello
//
// 0
//
//
// 6 is number of char in reply contents
// answer ends with sequence : "0\r\n" followed "\r\n".
//curl output is
//> GET / HTTP/1.1
// > User-Agent: curl/7.26.0
// > Host: localhost:8000
// > Accept: */*
// >
// * HTTP 1.1 or later with persistent connection, pipelining supported
// < HTTP/1.1 200 OK
// < Date: Wed, 26 Jun 2013 10:27:55 GMT
// < Content-Type:
// < Transfer-Encoding: chunked
// <
// hello
int main()
{
     int s;
     struct sockaddr_in serv;
     char request[]="GET / HTTP/1.1\r\nUser-Agent: socketTester\r\nAccept: */*\r\n\r\n";
     char buffer[900];
     for (char* p=buffer; p < buffer + sizeof(buffer); ++p)
       *p = 0;
     serv.sin_family= AF_INET;
     serv.sin_port = htons(8000);
     serv.sin_addr.s_addr = inet_addr("127.0.0.1");
// should resolve for name preferably
// pour ipv6 utiliser struct sockaddr_in6
     printf(" now trying to connect \n");
     if((s= socket(PF_INET, SOCK_STREAM, 0))<0) {
          perror("socket(): ");
          exit(1);
     }
     if (connect(s, (struct sockaddr *)&serv, (socklen_t)sizeof(struct sockaddr_in))<0) {
          perror("connect(): ");
          exit(1);
     }
     printf(" now sending http request \n");

     if(send(s, request, sizeof(request), 0)<0) {
          perror("send(): ");
          exit(1);
     }
     shutdown(s, 1); // We will no longer transmit
     size_t got = recv(s, buffer, sizeof(buffer), 0);
     if(got < 0) {
          perror("error in receiving(): \n");
          exit(1);
     }
     buffer[got] = 0;
     buffer[899]='\0';
     printf("server reply :\n\n%s\n\n",buffer);
     printf("\n buffer end \n");
     close(s);

     return 0;
}
