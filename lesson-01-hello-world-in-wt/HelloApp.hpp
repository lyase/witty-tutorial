#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <memory>
#include <Wt/WApplication>
#include <Wt/WString>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
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
    User *user;
    IWebPageFactory* mFactory ;
    void handlePathChanged(const std::string& newPath);
    MainWindow* mainWindow;
public:
    HelloApp(const Wt::WEnvironment& env);
    void setUserName(const Wt::WString& newName); 
    const Wt::WString userName();
    Wt::Dbo::Session& db();
    void saveUser(User* user);
    Wt::Dbo::ptr<User> findUser(const std::string name);
};

#endif // HELLOAPP_HPP
