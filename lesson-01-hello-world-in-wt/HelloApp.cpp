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
#include <Wt/WServer>
#include <Wt/Dbo/backend/Sqlite3>
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "MainWindow.hpp"
#include "IWebPageFactory.h"
#include "FactoryHelloWorldWebsite.hpp"
#include <Wt/Dbo/Exception>
#include <Wt/WCssTheme>
#include "models/User.h"
#include "Auth/Session.hpp"
#include "Auth/Services.hpp"


struct HelloApp::DBInfo : public Wt::WObject {
     Wt::Dbo::backend::Sqlite3 connection;
     ::Auth::Session session;
     DBInfo(Wt::WObject* parent, const std::string& dbConnString, const ::Auth::Services& services) :
          Wt::WObject(parent), connection(dbConnString), session(connection, services) {
          session.setConnection(connection);
     }
};
/*! \fn HelloApp::HelloApp(const Wt::WEnvironment& env)
* \brief a webapps  constructor
* the constructor  will Set up the _db a DBInfo()connection to  sqliteand map required tables from config file
* for dbo internal use
* \param a a Action .
*/
HelloApp::HelloApp(const Wt::WEnvironment& env, const ::Auth::Services& services) :
     Wt::WApplication(env)
{
     log("info") << "App created";
     setTheme(new Wt::WCssTheme("polished", this));
     setTitle("Hello world");
     // Set up the DB
     std::string dbConnString = "";
     const char* configSettingName = "DB"; // Set in tests/CMakeLists.txt
     readConfigurationProperty(configSettingName, dbConnString);
     if (dbConnString.empty())
          throw std::invalid_argument(std::string("Please set the ") + configSettingName + " in the configuration file");
     _db = new DBInfo(this, dbConnString, services);

     calc = new Calculator("/calc", this);

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
void HelloApp::handlePathChanged(const std::string& newPath)
{
     root()->clear();
     Wt::WContainerWidget* aroot=root();
     mFactory ->createWebPage(newPath, aroot);
     /* manual  way of doing things now implemented in the Factory ask the WebSiteFactory to create the required page
     if (newPath == "/ask")
         new AskWindow(root());
     else if (newPath == "/say")
         new SayWindow(root());
     else
         new MainWindow(root());
         */
}
void HelloApp::setUserName(const Wt::WString& newName)
{
     user->setName( newName.toUTF8());
}
const Wt::WString HelloApp::userName()
{
     return user->getName();
}

::Auth::Session& HelloApp::db()
{
     return _db->session;
}

void HelloApp::saveUser(User* user)
{
     Wt::Dbo::Transaction t(_db->session);
     _db->session.add(user);
     t.commit();
}

Wt::Dbo::ptr<User> HelloApp::findUser(const std::string name)
{
     Wt::Dbo::Transaction t(_db->session);
     return _db->session.find<User>().where("name = ?").bind(name);
}

int HelloApp::countUser(const std::string name)
{
     Wt::Dbo::Transaction t(_db->session);
     int count=0;
     try {
          count= _db->session.query<int>("select count(1) from user").where("name = ?").bind(name);
     } catch( exception& e) {
          cout <<"got exception: "<< e.what () <<"\n in countUser count is set to 0 \n";
          count= 0;
     }
     return count ;
}
