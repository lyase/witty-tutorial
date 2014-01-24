#pragma once
/** RESTful(ish) API
 */

#include <Wt/WApplication>
#include <Wt/WResource>
#include <Wt/Http/Response>

#include <string>

class Calculator : public Wt::WResource {
private:
public:
     Calculator(const std::string& path, Wt::WObject* parent=NULL)
          : Wt::WResource(parent) {
          setInternalPath(path);
          Wt::WApplication::instance()->log("info") << "Resource URL: " << url();
     }
     void handleRequest (const Wt::Http::Request&, Wt::Http::Response &response) {
          Wt::WApplication::instance()->log("info") << "Handle Request Called";
          response.setStatus(200);
          response.addHeader("Content-type", "text/plain");
          response.out() << "Hello\n";
     }
};
