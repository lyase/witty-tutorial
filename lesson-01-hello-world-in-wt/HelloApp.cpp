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
#include "HelloServer.hpp"
#include <Wt/Dbo/Session>
#include <Wt/Dbo/backend/Sqlite3>
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "MainWindow.hpp"
#include "IWebPageFactory.h"
#include "FactoryHelloWorldWebsite.hpp"
#include <Wt/Dbo/Exception>
#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>
#include "models/User.hpp"
#include "models/Post.hpp"

struct HelloApp::DBInfo : public Wt::WObject {
    Wt::Dbo::backend::Sqlite3 connection;
    Wt::Dbo::Session session;
    DBInfo(Wt::WObject* parent, const std::string& dbConnString) :
        Wt::WObject(parent), connection(dbConnString), session() {
        session.setConnection(connection);
        session.mapClass<AuthInfo>("auth_info");
        session.mapClass<AuthInfo::AuthIdentityType>("auth_identity");
        session.mapClass<AuthInfo::AuthTokenType>("auth_token");
        session.mapClass<Post>("post");
        try {
            session.createTables();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Using existing database" << std::endl;
        }
    }
};
/*! \fn HelloApp::HelloApp(const Wt::WEnvironment& env)
* \brief a webapps  constructor
* the constructor  will Set up the _db a DBInfo()connection to  sqliteand map required tables from config file
* for dbo internal use
* \param a a Action .
*/
HelloApp::HelloApp(const Wt::WEnvironment& env) :
    Wt::WApplication(env), _user(),
    mFactory(new FactoryHelloWorldWebsite(this)),
    auth(HelloServer::instance()->auth()),
    facebook(*HelloServer::instance()->facebook()) {
    setTitle("Hello world");
    // Set up the DB
    std::string dbConnString = "";
    const char* configSettingName = "DB"; // Set in tests/CMakeLists.txt
    readConfigurationProperty(configSettingName, dbConnString);
    if (dbConnString.empty())
        throw std::invalid_argument(std::string("Please set the ") + configSettingName + " in the configuration file");
    _db = new DBInfo(this, dbConnString);

    // Get the user to log in
    _authWidget = new Wt::Auth::AuthWidget(auth, *_users, _login, root());
    _authWidget->model()->addOAuth(&facebook);
    _authWidget->setRegistrationEnabled(true);

    // Finally navigate to where we are
    //internalPathChanged().connect(this, &HelloApp::handlePathChanged);
    //handlePathChanged(internalPath());
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
}

Wt::Dbo::Session& HelloApp::db() {
    return _db->session;
}
