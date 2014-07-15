#ifndef API_H
#define API_H
#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/Http/Response>
#include <Wt/Http/Request>

#include <functional>

#include <csignal>
class API : public Wt::WResource {
public:
     API();
     void handleRequest  (const Wt::Http::Request &request, Wt::Http::Response &response) ;
};

#endif // API_H
