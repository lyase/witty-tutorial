/** \file  HelloApp.cpp
*    Description:  code for the  web app a wt Hello world in c++
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:
 *
 * =====================================================================================
 */

#include "HelloApp.hpp"
#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Sqlite3>
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "MainWindow.hpp"
#include "IWebPageFactory.h"
#include "FactoryHelloWorldWebsite.hpp"
#include "User.h"

struct HelloApp::DBInfo : public Wt::WObject {
    Wt::Dbo::backend::Sqlite3 connection;
    Wt::Dbo::Session session;
    DBInfo(Wt::WObject* parent, const std::string& dbConnString) :
           Wt::WObject(parent), connection(dbConnString), session() {
        session.setConnection(connection);
        session.mapClass<Post>("post");
        session.mapClass<User>("user");
    }
};

HelloApp::HelloApp(const Wt::WEnvironment& env) :
        Wt::WApplication(env) {
    setTitle("Hello world");
    // Set up the DB
    std::string dbConnString = "";
    const char* configSettingName = "DB"; // Set in tests/CMakeLists.txt
    readConfigurationProperty(configSettingName, dbConnString);
    if (dbConnString.empty())
        throw std::invalid_argument(std::string("Please set the ") + configSettingName + " in the configuration file");
    _db = new DBInfo(this, dbConnString);
    // Pretend we know who the user is
    user = new User();
    // Fire up the page generator
    mFactory = new FactoryHelloWorldWebsite(this);
    // Finally navigate to where we are
    internalPathChanged().connect(this, &HelloApp::handlePathChanged);
    handlePathChanged(internalPath());

}
/**
* \fn void void HelloApp::handlePathChanged(const std::string& newPath)
* \brief this function will be called each time the user changes webpage
* this function should create the view ( web page) by instantiating the apropriate Window object a  Wt::WContainerWidget
* \param newPath contains path of the page been asked
*
 * \return nothing
*/
void HelloApp::handlePathChanged(const std::string& newPath) {
    root()->clear();
    Wt::WContainerWidget* aroot=root();
    mFactory ->createWebPage(newPath, aroot);
    /* manual  way of doing things now implemented in the Factory
    if (newPath == "/ask")
        new AskWindow(root());
    else if (newPath == "/say")
        new SayWindow(root());
    else
        new MainWindow(root());
        */
}
void HelloApp::setUserName(const Wt::WString& newName) {
    user->setName( newName.toUTF8());
}
const Wt::WString HelloApp::userName() {
    return user->getName();
}

Wt::Dbo::Session& HelloApp::db() {
    return _db->session;
}

void HelloApp::saveUser(User* user) {
    Wt::Dbo::Transaction t(_db->session);
   _db->session.add(user);
    t.commit();
}

Wt::Dbo::ptr<User> HelloApp::findUser(const std::string name) {
    Wt::Dbo::Transaction t(_db->session);
    return _db->session.find<User>().where("name = ?").bind(name);
}

