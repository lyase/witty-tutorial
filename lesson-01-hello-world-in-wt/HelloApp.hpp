#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <memory>
#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/Dbo/Session>
#include <Wt/Auth/Login>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/AuthService>
#include <Wt/Auth/AuthWidget>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
#include "models/User.hpp"

typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

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

    UserDatabase *_users;
    Wt::Auth::AuthWidget* _authWidget;
    Wt::Auth::Login _login;
public:
    HelloApp(const Wt::WEnvironment& env);
    Wt::Dbo::Session& db();

    Wt::Auth::AbstractUserDatabase& users();
    Wt::Auth::Login& login() {
        return _login;
    }
    const Wt::Auth::AuthService& auth;
    const Wt::Auth::FacebookService& facebook;
};

#endif // HELLOAPP_HPP
