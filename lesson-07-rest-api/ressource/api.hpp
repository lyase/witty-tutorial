#ifndef API_H
#define API_H
#include <Wt/WServer>
#include <Wt/WResource>
#include <Wt/Http/Response>
#include <Wt/Http/Request>

#include <functional>

#include <csignal>
/*! A API   class
* \details This class is to be used in a witty application it will serve on url following json as string {\"name\": \"Super man\", \"age\": 12}
* . usage
*
*add a single entry point, at the default location (as determined
*by the server configuration's deploy-path)
*  \code{.cpp}             API api;
*       server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
*       server.addResource(&api, "/");
*          if (server.start())
* \endcode
* \author Lyase damasked frommattew sherborne initial implementation
* \version 4.1a
* \date 1990-2012
* \pre First initialize the witty server before adding this served ressource .
* \bug none known ;)

*/
/*! \brief  this class defines a json ressource
*/
class API : public Wt::WResource {
public:
     API();
     void handleRequest  (const Wt::Http::Request &request, Wt::Http::Response &response) ;
};

#endif // API_H
