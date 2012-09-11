/** \file  functional_test.cpp
*source file for test of the application  ie. HelloApp object
* you should put here all test related to the application functionalities
* think HelloApp object as a Controller providing strategies (methods) to the views to interact with the Apps Objects User.....
* and updating the views( window) sending the correct window to user as user operates the app
*\b compiles with \code g++  \endcode
*\n
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:
 *
 * =====================================================================================
 */

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/Test/WTestEnvironment>
#include <Wt/WSignal>
#include <Wt/WAnchor>
#include "../HelloApp.hpp"
#include "../MainWindow.hpp"
#include "utils/helper.hpp"
#include <Wt/Test/WTestEnvironment>
#include <boost/test/unit_test.hpp>
#include "../HelloApp.hpp"
#include "../User.h"
#include <Wt/WApplication>
#include <Wt/Test/WTestEnvironment>
#include <boost/test/unit_test.hpp>
#include "../HelloApp.hpp"
#include <Wt/Dbo/backend/Sqlite3>
#include <boost/filesystem.hpp>
#include "../User.h"
struct LiveAppFixture {
    Wt::Test::WTestEnvironment env;
    HelloApp app;
    dbo::Session& session;
    LiveAppFixture(bool createTables=false) : env(".", "wt-config.xml"), app(env, "blog.db"), session(app.db())  {
        app.initialize();
        if (createTables)
            session.createTables();
    }
    // the tearDown
    ~LiveAppFixture() {
            session.flush();
            boost::filesystem::remove("./blog.db");
        }

    MainWindow* getMainWindow() {
        // We are getting a handle on the MainWindow
        Wt::WWidget* result = app.root()->widget(0);
        return dynamic_cast<MainWindow*>(result);
    }
};
void saveUser(User* user, Wt::Dbo::Session& session) {
    Wt::Dbo::Transaction t(session);
    session.add(user);
    t.commit();
}

Wt::Dbo::ptr<User> findUser(const std::string name, Wt::Dbo::Session& session) {
    Wt::Dbo::Transaction t(session);
    return session.find<User>().where("name = ?").bind(name);
}


// we are testing here:
//if the app can create  it's landing page
BOOST_FIXTURE_TEST_SUITE( FunctionalSuite, LiveAppFixture );

BOOST_AUTO_TEST_CASE( testMainWindowExists ) {
    MainWindow* main = getMainWindow();
    BOOST_REQUIRE(main);
}
// we are testing here:
//the application can change the name of the current user
//this is mostly an developper test howto test a functionality of the app
BOOST_AUTO_TEST_CASE( testuserNameManagement ) {

    if (app.userName() == "John") {
        std::cerr << "name is already john precondition is not met I can not run this test the current name is  " << app.userName() << std::endl;
        // pre condition not met test should fail
        BOOST_CHECK_EQUAL( 0, 1 );
    } else {
        app.setUserName("John");
        //std::string name = app.userName();
        BOOST_CHECK_EQUAL( app.userName(), "John" );
    }
}
// we are testing here:
//clicking the link to ask page  from the  landing page we
//can  will change the path to the ask window
// currently this is not testing the windows funcionality as a user case would
//ultimately this should be tested using something like selenium
BOOST_AUTO_TEST_CASE( testAskLink ) {
    MainWindow* main = getMainWindow();
    BOOST_REQUIRE(main);
    cout<<"before click path is "<< app.internalPath() << endl;
    BOOST_REQUIRE( app.internalPath() != "/ask" );
    test_helpers::click(main->_askLink);
    BOOST_CHECK_EQUAL( app.internalPath(), "/ask" );
}
BOOST_AUTO_TEST_CASE( testUserPersistence ) {
    // Create an app
    Wt::Test::WTestEnvironment env1(".", "wt-config.xml");
    HelloApp app1(env1, "blog.db");
    app1.initialize();
    { // Scope brackets so that session1 is deleted before session2 is created
    // Create the first Session
    LiveAppFixture session1(true);
    // Create a user
    User *user1 = new User(); // session.add takes ownership of this and deletes it when the session dies
    user1->setName("mister cool");
    user1->setPassword("its a secret");
    user1->setRole(Alien);
    user1->setKarma(15);
    BOOST_REQUIRE_EQUAL(user1->getName(), "mister cool");
    BOOST_REQUIRE_EQUAL(user1->getPassword(), "its a secret");
    BOOST_REQUIRE_EQUAL(user1->getRole(), Alien);
    BOOST_REQUIRE_EQUAL(user1->getKarma(), 15);
    // Save it
    app1.saveUser(user1, session1.session);
    // Kill the app
    app1.quit();
    }
    // Start a new app
    Wt::Test::WTestEnvironment env2(".", "wt-config.xml");
    HelloApp app2(env2);
    app2.initialize();
    // Create the second Session
    LiveAppFixture session2(false);
    // Search for the user object in the db
    Wt::Dbo::ptr<User> user2 = app2.findUser("mister cool", session2.session);
    // Check the details are the same
    BOOST_REQUIRE(user2);
    BOOST_REQUIRE_EQUAL(user2->getName(), "mister cool");
    BOOST_REQUIRE_EQUAL(user2->getPassword(), "its a secret");
    BOOST_REQUIRE_EQUAL(user2->getRole(), Alien);
    BOOST_REQUIRE_EQUAL(user2->getKarma(), 15);
}


BOOST_AUTO_TEST_SUITE_END();
