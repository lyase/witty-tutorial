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

// RAII for a socket
struct SocketResource {
    int s;
    SocketResource() : s(socket(PF_INET, SOCK_STREAM, 0)) {}
    ~SocketResource() {
        close(s);
    }
    /// Call this after you have sent your last bit to destroy
    /// the transmit buffers and to allow the socket to close
    void doneTransmitting() {
        shutdown(s, 1);
    }
    operator int() const {
        return s;
    }
};

struct Socket {
    SocketResource s;
    sockaddr_in server_address;
    Socket(const char* host_name, unsigned short port=80) {
        // Set up the address
        server_address.sin_family= AF_INET;
        server_address.sin_port = htons(port);
        server_address.sin_addr.s_addr = inet_addr(host_name);
    }
    void request(const char* req) {
        // TODO: Add the ability to make up your own requests, like addHeader, etc.
        if(s < 0) {
            //throw std::runtime_error("Couldn't open socket");
            perror("socket(): ");
            exit(1);
        }
        if (connect(s, (struct sockaddr *)&server_address, (socklen_t)sizeof(struct sockaddr_in))<0) {
            perror("connect(): ");
            exit(1);
        }
        printf("Now sending http request \n");

        if(send(s, req, strlen(req), 0)<0) {
            perror("send(): ");
            exit(1);
        }
        shutdown(s, 1); // We will no longer transmit
    }
    std::string getBody() {
        // Get the result
        std::string buffer(900, '\0');
        size_t got = recv(s, &buffer[0], buffer.size(), 0);
        if(got < 0) {
            perror("error in receiving(): \n");
            exit(1);
        }
        // Get the body of the response
        buffer.resize(got);
        size_t start_of_body = buffer.find("\r\n\r\n");
        size_t end_of_body = buffer.find("\r\n\r\n", start_of_body);
        // TODO: decode chunked encoding
        return decodeChunkedEncoding(buffer.substr(start_of_body, end_of_body));
    }
    std::string decodeChunkedEncoding(std::string body) {
        std::stringstream data(body);
        std::string output;
        output.reserve(body.size());
        int chunkSize;
        data >> chunkSize;
        data.get(); // \r
        data.get(); // \n
        while (chunkSize != 0) {
            std::copy_n(std::istream_iterator<char>(data), chunkSize, std::back_inserter(output));
            data >> chunkSize;
        }
        return output;
    }
};

int main()
{
    Socket socket("127.0.0.1", 8000);
    socket.request("GET / HTTP/1.1\r\nUser-Agent: socketTester\r\nAccept: */*\r\n\r\n");

    std::string body = socket.getBody();

    cout << "BODY: " << endl << body << endl << "</BODY>" << endl;

    return 0;
}
