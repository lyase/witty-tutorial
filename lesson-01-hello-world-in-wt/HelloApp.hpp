#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <memory>
#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/Dbo/Session>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
#include "UserManagement.hpp"
#include "User.h"

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
    class DBInfo;
    DBInfo* _db;
    Wt::WString _userName;
    Wt::Dbo::ptr<User> _user;
    IWebPageFactory* mFactory ;
    void handlePathChanged(const std::string& newPath);
    MainWindow* mainWindow;
public:
    HelloApp(const Wt::WEnvironment& env);
    Wt::Dbo::Session& db();
    UserManagement users;
};

#endif // HELLOAPP_HPP
