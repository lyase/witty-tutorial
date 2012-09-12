#include <string>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <Wt/Test/WTestEnvironment>
#include "../HelloApp.hpp"

struct DBCleaner {
    ~DBCleaner() {
        Wt::Test::WTestEnvironment env(".", "wt-config.xml");
        HelloApp app(env);
        app.db().dropTables();
    }
};

BOOST_AUTO_TEST_SUITE( testUserPersistenceSuite )

BOOST_AUTO_TEST_CASE( testUserPersistence ) {
    DBCleaner cleaner; // When this obj goes out of scope, it'll drop the tables in the db
    { // Scope brackets so that app1 is deleted before session2 is created
    // Create an app
    Wt::Test::WTestEnvironment env1(".", "wt-config.xml");
    HelloApp app1(env1);
    app1.initialize();
    app1.db().createTables();
    // Create the first Session
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
    app1.saveUser(user1);
    // Kill the app
    app1.quit();
    }
    // Start a new app
    Wt::Test::WTestEnvironment env2(".", "wt-config.xml");
    HelloApp app2(env2);
    app2.initialize();
    // Create the second Session
    // Search for the user object in the db
    Wt::Dbo::ptr<User> user2 = app2.findUser("mister cool");
    // Check the details are the same
    BOOST_REQUIRE(user2);
    BOOST_REQUIRE_EQUAL(user2->getName(), "mister cool");
    BOOST_REQUIRE_EQUAL(user2->getPassword(), "its a secret");
    BOOST_REQUIRE_EQUAL(user2->getRole(), Alien);
    BOOST_REQUIRE_EQUAL(user2->getKarma(), 15);
    // delete the filesystem
}

BOOST_AUTO_TEST_SUITE_END()
