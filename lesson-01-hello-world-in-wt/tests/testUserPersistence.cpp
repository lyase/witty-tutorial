/**
  * A functional test that makes sure a user object can be created and saved, then a different App instance can read it from the DB
 **/
 
#include <Wt/WApplication>
#include <Wt/Test/WTestEnvironment>
#include <boost/test/unit_test.hpp>
#include "../HelloApp.hpp"
#include "../User.h"

BOOST_AUTO_TEST_SUITE( UserPersistence );

namespace {
    struct SessionMaster {
        dbo::backend::Sqlite3 sqlite3;
        dbo::Session session;
        SessionMaster(bool createTables) : sqlite3("blog.db") {
            session.setConnection(sqlite3);
            session.mapClass<Post>("post");
            session.mapClass<User>("user");
            if (createTables)
                session.createTables();
        }
    };
    
    void saveUser(User* user, Wt::Dbo::Session& session) {
        Wt::Dbo::Transaction t(session);
        session.add(user);
        t.commit();
    }
}

BOOST_AUTO_TEST_CASE( testUserPersisitence ) {
    // Create an app
    Wt::Test::WTestEnvironment env1(".", "wt-config.xml");
    HelloApp app1(env1);
    app1.initialize();
    // Create the first Session
    SessionMaster* session1 = new SessionMaster(true);
    // Create a user
    User *user1 = new User();
    user1->setName("mister cool");
    user1->setPassword("its a secret");
    user1->setRole(Alien);
    user1->setKarma(15);
    BOOST_REQUIRE_EQUAL(user1->getName(), "mister cool");
    BOOST_REQUIRE_EQUAL(user1->getPassword(), "its a secret");
    BOOST_REQUIRE_EQUAL(user1->getRole(), Alien);
    BOOST_REQUIRE_EQUAL(user1->getKarma(), 15);
    // Save it
    saveUser(user1, session1->session);
    // Kill the app
    app1.quit();
    delete session1;
    // Start a new app
    Wt::Test::WTestEnvironment env2(".", "wt-config.xml");
    HelloApp app2(env2);
    app2.initialize();
    // Create the second Session
    SessionMaster* session2 = new SessionMaster(false);
    // Search for the user object in the db
    Wt::Dbo::Transaction t(session2->session);
    BOOST_REQUIRE_EQUAL(user1->getName(), "mister cool");
    Wt::Dbo::ptr<User> user2 = \
         session2->session.find<User>().where("name = ?").bind(user1->getName());
    // Check the details are the same
    BOOST_REQUIRE(user2);
    BOOST_REQUIRE_EQUAL(user2->getName(), "mister cool");
    BOOST_REQUIRE_EQUAL(user2->getPassword(), "its a secret");
    BOOST_REQUIRE_EQUAL(user2->getRole(), Alien);
    BOOST_REQUIRE_EQUAL(user2->getKarma(), 15);
}

BOOST_AUTO_TEST_SUITE_END();
