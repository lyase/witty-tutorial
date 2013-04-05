/** \file  testUser_Class_dbo.cpp
*    Description:  minimal application using dbo for User class from :
* http://www.webtoolkit.eu/wt/doc/tutorial/dbo.html
*shows how to use dbo functionality with User class

*\b compiles with \code g++listing.cpp User.cpp testUser_Class_dbo.cpp -o testdbo -l wtdbosqlite3 \endcode
*\b run with
*\code  rm blog.db ; ./testdbo \endcode
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
#include "models/User.h"
#include "listing.h"

#include <string>
#include <iostream>
#include <string>
#include <iostream>

#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Dbo>

#include <boost/filesystem.hpp>

using namespace std;

/*
* note Try to create the schema (will fail if already exists delete database first).
*/
/** a structure used to have fixture for the  tests \n
*the constructor will be called before each test should be used  as the setup() \n
*the destructor will be called after every test should be used as teardown().
*/

struct CMyFooTestFixture {
     // TODO: Declare some common values accesses in tests here.
     User *user;/**< the a object user to be used in each test  */
     /*! \fn CMyFooTestFixture()
     * \brief constructor
     * to be used as fixture setup() \n
     * initialise here all you need for  the tests
     */
     CMyFooTestFixture() {
          // TODO: Common set-up each test case here.

          user = new User();
     }
     /*! \fn ~CMyFooTestFixture()
     * \brief destructor
     * to be used as fixture teardown() \n
     * clean all here
     */
     ~CMyFooTestFixture() {
          // TODO: Common tear-down after  each test case here.
          delete user;
          user=0;
          // Delete the sqlite db
          boost::filesystem::remove("./blog.db");

     }
     // TODO: Possibly put some function common to  tests.
     void TestSaveLoad(User& user, bool asBinary) {
     }

};
/*! \fn int main ()
* \brief a complete database operation
* create database \n
* create table for user \n
* create & store a user \n
* get and display all User object from database \n
* update   karma field of user Joe\n
* get and display updated  User Joe object from database \n
* delete user joe from database \n
* \return nothing
*/
int main ()
{
     CMyFooTestFixture a;
     cout<<" Create database connection \n";
     dbo::backend::Sqlite3 sqlite3("blog.db");
     dbo::Session session;
     session.setConnection(sqlite3);
     createTableForUser(&session);
     createUserJoe(&session);
     readUserJoe(&session);
     cout <<" updating user joe ";
     readUserJoeOnly(&session);
     cout <<" updating user joe ";
     updateUserJoeOnly(&session);
     cout <<" printing updated  user joe ";
     readUserJoeOnly(&session);
     cout<< "deleting user joe";
     deleteUserJoeOnly(&session);
     readUserJoe(&session);
     cout <<" looking for unknow user ";
     read_UnknownUserthrowsexception(&session);

}
/*

BOOST_FIXTURE_TEST_SUITE(UserTestSuite, CMyFooTestFixture);

BOOST_AUTO_TEST_CASE(SettingUserName)
{
    user->setName("  foooooo ");
    BOOST_CHECK_EQUAL(user->getName(), "  foooooo ");
}

BOOST_AUTO_TEST_SUITE_END();
*/
