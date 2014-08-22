#include <string>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <Wt/Test/WTestEnvironment>
#include "../HelloApp.hpp"
#include "../Auth/Services.hpp"
#include "LiveAppFixture.hpp"

BOOST_FIXTURE_TEST_SUITE( testUserPersistenceSuite, LiveAppFixture );



BOOST_AUTO_TEST_CASE( testUserPersistence )
{
     DBCleaner*cleaner = new DBCleaner; // When this obj goes out of scope, it'll drop the tables in the db

     lesson01Auth::Services services;
     // Scope brackets so that app1 is deleted before session2 is created
     // Create an app
     Wt::Test::WTestEnvironment env1("..", "../wt-config.xml");
     HelloApp app1(env1, services);
     app1.initialize();

     cout<< " checking i can query database before any operation it sould be  empty \n";
     int count =  app1.countUser("mister cool");
     cout << " user count is: "<< count <<"\n" ;
     BOOST_REQUIRE_EQUAL(count, 0);
     cout <<"test finish\n";
     //Wt::Dbo::ptr<User> Mistercool = app1.findUser("mister cool");


     // Create the first Session
     // Create a user and save it to database
     User *user1 = new User(); // session.add takes ownership of this and deletes it when the session dies
     user1->setName("mister cool");
     user1->setPassword("its a secret");
     user1->setRole(Alien);
     user1->setKarma(15);
     // checking setter & getter works for user class
     BOOST_REQUIRE_EQUAL(user1->getName(), "mister cool");
     BOOST_REQUIRE_EQUAL(user1->getPassword(), "its a secret");
     BOOST_REQUIRE_EQUAL(user1->getRole(), Alien);
     BOOST_REQUIRE_EQUAL(user1->getKarma(), 15);
     app1.saveUser(user1);
// query the current  database  check the user is now in database
     Wt::Dbo::ptr<User> Mistuser21 = app1.findUser("mister cool");
     cout<< "after insert in app1 I query mister cool his name is:"<< Mistuser21->getName()<<"\n";
     BOOST_REQUIRE_EQUAL(Mistuser21->getName(), "mister cool");
     // Kill the app
     app1.quit();

     lesson01Auth::Services services2;
     // Start a app2 a new app checking now the user information were saved to database in earlier database operation
     Wt::Test::WTestEnvironment env2("..", "../wt-config.xml");
     HelloApp app2(env2, services2);
     app2.initialize();
     //    app2.Dbinitialize(); not required done as app starts dbconnection mapping by default
     // Create the second Session
     // Search for the user object in the db
     int count2 =  app2.countUser("mister cool");
     cout << " user count2 is: "<< count2 <<"\n" ;
     BOOST_REQUIRE_EQUAL(count2, 1);
     // Check the details are the same
     Wt::Dbo::ptr<User> user2 = app2.findUser("mister cool");
     BOOST_REQUIRE(user2);
     BOOST_REQUIRE_EQUAL(user2->getName(), "mister cool");
     BOOST_REQUIRE_EQUAL(user2->getPassword(), "its a secret");
     BOOST_REQUIRE_EQUAL(user2->getRole(), Alien);
     BOOST_REQUIRE_EQUAL(user2->getKarma(), 15);
     // delete the database files cleanup filesystem
     delete cleaner;
}

BOOST_AUTO_TEST_SUITE_END();
