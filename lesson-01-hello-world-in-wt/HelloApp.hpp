#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Sqlite3>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
#include "User.h"

class HelloApp : public Wt::WApplication {
private:
    Wt::WString _userName;
    User *user;
    IWebPageFactory* mFactory ;
    Wt::Dbo::backend::Sqlite3 dbBackend;
    Wt::Dbo::Session _db;
    void handlePathChanged(const std::string& newPath);
    MainWindow* mainWindow;
public:
    HelloApp(const Wt::WEnvironment& env, const std::string& dbConnString);
    void setUserName(const Wt::WString& newName); 
    const Wt::WString userName();
    Wt::Dbo::Session& db();
    void saveUser(User* user);
    Wt::Dbo::ptr<User> findUser(const std::string name);
    void first_Dbinitialize();
    void Dbinitialize();
};

#endif // HELLOAPP_HPP
