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
class Session;
namespace backend {
class Sqlite3;
}
}
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
     HelloApp(const Wt::WEnvironment& env);
     void setUserName(const Wt::WString& newName);
     const Wt::WString userName();
     Wt::Dbo::Session& db();
     void saveUser(User* user);
     Wt::Dbo::ptr<User> findUser(const std::string name);
     int countUser(const std::string name);
     void first_Dbinitialize();
     void Dbinitialize();
     Calculator* calc;
};

#endif // HELLOAPP_HPP
