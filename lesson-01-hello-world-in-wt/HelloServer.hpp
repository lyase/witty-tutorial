#ifndef HELLOSERVER_H
#define HELLOSERVER_H

#include <memory>
#include <Wt/WServer>
#include <Wt/Auth/AuthService>
#include <Wt/Auth/FacebookService>
#include <Wt/Auth/HashFunction>


class HelloServer : public Wt::WServer {
private:
     Wt::Auth::AuthService _auth;
     std::unique_ptr<Wt::Auth::FacebookService> _facebookAuth;
     Wt::Auth::BCryptHashFunction _hashFunction;
public:
     HelloServer(const std::string &wtApplicationPath=std::string(), const std::string &wtConfigurationFile=std::string());
     const Wt::Auth::AuthService& auth() {
          return _auth;
     }
     const Wt::Auth::FacebookService* facebook() {
          return _facebookAuth.get();
     }
     static HelloServer* instance() {
          return dynamic_cast<HelloServer*>(Wt::WServer::instance());
     }
};

#endif // HELLOSERVER_H
