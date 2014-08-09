#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/WIOService>

#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/Json/Object>

#include <iostream>

#include <boost/system/error_code.hpp>

struct Client {
     Wt::Http::Client api;
     Wt::Http::Message last_msg;
     Client(Wt::WIOService& io) : api(io) {
          api.done().connect(this, &Client::gotResponse);
          api.setTimeout(10);
     }
     bool test() {
          return api.get("http://localhost:8000/");
     }
     void gotResponse(boost::system::error_code code, Wt::Http::Message msg) {
          last_msg = msg;
     }
};



int runClient()
{
     using std::cout;
     using std::endl;

     cout << "Initializing client connection...\n" << endl;
     Wt::WIOService io;
     io.start();
     Client client(io);
     cout << "Sending Request..." << endl;
     bool sent = client.test();
     if (sent)
          cout << "Sent Request" << endl;
     else {
          cout << "Could not send!" << endl;
          return -1;
     }
     cout << "Waiting for completion..." << endl;
     io.stop();

     cout << "Body: " << client.last_msg.body() << endl;
     cout << "status code: " << client.last_msg.status() << endl;

     Wt::Json::Object result;
     Wt::Json::parse(client.last_msg.body(), result);

     std::string name = result.get("name");
     int age = result.get("age");

     cout << "name: " << name << endl;
     cout << "age: " << age << endl;

     io.stop();

     if (client.last_msg.body() == "hello\n")
          return 0;
     else
          return 1;
}

