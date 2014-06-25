#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <memory>
#include <Wt/WApplication>
#include <Wt/WString>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
#include "models/User.h"
#include "models/dbinfo.hpp"
#include "calc.hpp"

namespace Wt {
namespace Dbo {
namespace backend {
class Sqlite3;
}
}
}

namespace lesson01Auth {
class Session;
class Services;
}

class HelloApp : public Wt::WApplication {
private:
     DBInfo* _db;
     Wt::WString _userName;
     User *user;
     IWebPageFactory* mPageFactory ;
     void handlePathChanged(const std::string& newPath);
public:
     HelloApp(const Wt::WEnvironment& env, const lesson01Auth::Services& services);
     void setUserName(const Wt::WString& newName);
     const Wt::WString userName();
     ::Auth::Session& session();
     void saveUser(User* user);
     Wt::Dbo::ptr<User> findUser(const std::string name);
     int countUser(const std::string name);
     Calculator* calc;
     Wt::Dbo::collection< Wt::Dbo::ptr<User> > userList();
};

#endif // HELLOAPP_HPP
