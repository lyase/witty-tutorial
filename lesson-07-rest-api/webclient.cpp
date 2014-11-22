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
#include <stdexcept>
#include <iterator>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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

struct SSLSocket {
    /// To be run at the start of the program
    static void init() {
        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();
        SSL_library_init();
    }
    BIO* bio;
    SSL_CTX * ctx;
    SSL* ssl;
    char buf[256];
    SSLSocket(const char* hostnamePort) {
        ctx = SSL_CTX_new(SSLv23_client_method());
        if (!ctx)
            throw std::runtime_error(ERR_reason_error_string(ERR_get_error()));
        bio = BIO_new_ssl_connect(ctx);
        BIO_get_ssl(bio, & ssl);
        SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
        BIO_set_conn_hostname(bio, hostnamePort);
        if(BIO_do_connect(bio) <= 0)
            throw std::runtime_error("Couldn't connect");
        // We don't verify the cert yet..
        //if(! SSL_CTX_load_verify_locations(ctx, "/path/to/TrustStore.pem", NULL))
        //if(SSL_get_verify_result(ssl) != X509_V_OK)
    }
    ~SSLSocket() {
        SSL_CTX_free(ctx);
        BIO_free_all(bio);
    }
    void read(std::string& out) {
        int numBytes = BIO_read(bio, buf, sizeof(buf));
        while (numBytes > 0) {
            if(numBytes == 0)
                throw std::runtime_error("Connection is closed");
            else if(numBytes < 0) {
                if(! BIO_should_retry(bio))
                    throw std::runtime_error("Couldn't read");
                else
                    throw std::runtime_error("Couldn't read. Retry");
            }
            out.reserve(out.size() + numBytes);
            std::copy(buf, buf + numBytes, std::back_inserter(out));
            numBytes = BIO_read(bio, buf, sizeof(buf));
        }
    }
    void write(const std::string& in) {
        if(BIO_write(bio, in.c_str(), in.size()) <= 0)
            if(! BIO_should_retry(bio))
                throw std::runtime_error("Couldn't write");
            else
                throw std::runtime_error("Couldn't write. Retry");
    }
};

int main()
{
    // Prepare OpenSSL
    SSLSocket::init();

    SSLSocket s("127.0.0.1:8443");
    s.write("GET / HTTP/1.1\r\nUser-Agent: socketTester\r\nAccept: */*\r\n\r\n");
    std::string msg;
    s.read(msg);

    // Get the msg of the response
    const std::string marker="\r\n\r\n";
    auto start_of_body =
        search(msg.begin(), msg.end(), marker.begin(), marker.end()) + marker.size();
    auto end_of_body =
        search(start_of_body, msg.end(), marker.begin(), marker.end());
    ++start_of_body; // For some reason we get '0' in the reply
    --end_of_body; // For some reason we get '0' at the end too

    std::string body;
    body.reserve(msg.end() - start_of_body);
    copy(start_of_body, msg.end(), back_inserter(body));

    std::cout << "body: " << body << std::endl;

    return 0;
}
