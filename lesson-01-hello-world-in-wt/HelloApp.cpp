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
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "MainWindow.hpp"
#include "IWebPageFactory.h"
#include "FactoryHelloWorldWebsite.hpp"
#include "User.h"

HelloApp::HelloApp(const Wt::WEnvironment& env, const std::string& dbConnString) :
        Wt::WApplication(env), dbBackend(dbConnString) {
    setTitle("Hello world");
    user = new User();
    mFactory = new FactoryHelloWorldWebsite(this);
    internalPathChanged().connect(this, &HelloApp::handlePathChanged);
    // Set up DB
    _db.setConnection(dbBackend);
    _db.mapClass<Post>("post");
    _db.mapClass<User>("user");
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
    return _db;
}

void HelloApp::saveUser(User* user) {
    Wt::Dbo::Transaction t(_db);
    _db.add(user);
    t.commit();
}

Wt::Dbo::ptr<User> HelloApp::findUser(const std::string name) {
    Wt::Dbo::Transaction t(_db);
    return _db.find<User>().where("name = ?").bind(name);
}

