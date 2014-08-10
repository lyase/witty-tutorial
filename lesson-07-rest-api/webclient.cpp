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
#include <sstream>
#include <iterator>
#include <algorithm>
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
/*
 you can https
https requests look just like http requests, but with transparent encryption of the actual communication between the client and the server, and on a different default port. The good news is that transparent encryption allows you to program just like you're writing a regular HTTP client. The bad news is that the encryption is complex enough that you need a specialized library to implement it for you.

One such library is OpenSSL. Using OpenSSL, the minimal code for a client would look like this:
#include <openssl/ssl.h>

// first connect to the remote as usual, but use the port 443 instead of 80

// initialize OpenSSL - do this once and stash ssl_ctx in a global var
SSL_load_error_strings ();
SSL_library_init ();
SSL_CTX *ssl_ctx = SSL_CTX_new (SSLv23_client_method ());

// create an SSL connection and attach it to the socket
SSL *conn = SSL_new(ssl_ctx);
SSL_set_fd(conn, sock);

// now proceed with HTTP traffic, using SSL_read instead of recv() and
// SSL_write instead of send(), and SSL_shutdown/SSL_free before close()
 */
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
     close(s);

     // Get the body of the response
     buffer[got] = 0;
     const char* in = buffer;
     const char* end = buffer + got;
     const char marker[]="\r\n\r\n";
     const char *start_of_body =
         search(in, end, marker, marker + sizeof(marker) - 1) + sizeof(marker);
     const char *end_of_body =
         search(start_of_body, end, marker, marker + sizeof(marker) - 1);
     ++start_of_body; // For some reason we get '0' in the reply
     --end_of_body; // For some reason we get '0' at the end too

     std::string body;
     body.reserve(end_of_body - start_of_body);
     copy(start_of_body, end_of_body, back_inserter(body));

     cout << "BODY: " << endl << body << endl << "</BODY>" << endl;

     return 0;
}
