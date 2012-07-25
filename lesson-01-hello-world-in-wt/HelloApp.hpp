#ifndef HELLOAPP_HPP
#define HELLOAPP_HPP

#include <Wt/WApplication>
#include <Wt/WString>
#include "IWebPageFactory.h"
#include "MainWindow.hpp"
#include "User.h"

class HelloApp : public Wt::WApplication {
private:
    Wt::WString _userName;
    User *user;
    IWebPageFactory* mFactory ;
    void handlePathChanged(const std::string& newPath);
    MainWindow* mainWindow;
public:
    HelloApp(const Wt::WEnvironment& env);
    void setUserName(const Wt::WString& newName); 
    const Wt::WString userName();
};

#endif // HELLOAPP_HPP
