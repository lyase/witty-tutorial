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
    void handlePathChanged(const std::string& newPath);
    MainWindow* mainWindow;
public:
    HelloApp(const Wt::WEnvironment& env,WebPageFactory&);
    void setUserName(const Wt::WString& newName) 
    { user->setName( newName.toUTF8()); }
    const Wt::WString userName()
    { return user->getName(); }
};

#endif // HELLOAPP_HPP
