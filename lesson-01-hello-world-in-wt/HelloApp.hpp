#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <memory>
#include <Wt/WApplication>
#include <Wt/WString>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
#include "models/User.h"
#include "calc.hpp"

namespace Wt {
namespace Dbo {
namespace backend {
class Sqlite3;
}
}
}

namespace Auth {
    class Session;
    class Services;
}

class HelloApp : public Wt::WApplication {
private:
     struct DBInfo;
     DBInfo* _db;
     Wt::WString _userName;
     User *user;
     IWebPageFactory* mFactory ;
     void handlePathChanged(const std::string& newPath);
public:
     HelloApp(const Wt::WEnvironment& env, const Auth::Services& services);
     void setUserName(const Wt::WString& newName);
     const Wt::WString userName();
     ::Auth::Session& db();
     void saveUser(User* user);
     Wt::Dbo::ptr<User> findUser(const std::string name);
     int countUser(const std::string name);
     Calculator* calc;
};

#endif // HELLOAPP_HPP
