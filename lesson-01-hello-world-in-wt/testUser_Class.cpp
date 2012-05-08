/** \file  testUser_Class.cpp
*    Description:  tests(boost framework)
*checking functionality and documenting basic usage of User class 
to be really complete I need to add tests for dbo functionality of the user class but so far it is too hard for me .
*\b compiles & run  with : \code //g++ -g -lboost_unit_test_framework  -o tests testUser_Class.cpp && ./tests --log_level=test_suite --report_level=short \endcode
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
#define BOOST_TEST_MODULE UserTestSuite
#define BOOST_TEST_DYN_LINK
#include "User.h"
#include <string>
#include <iostream>
#include <boost/test/unit_test.hpp>
using namespace std ;
/** a structure used to have fixture for test \n 
     *the contructor can be seen as the setup() \n
     the destructor as teardown().
  */

struct CMyFooTestFixture
{
  /*! \fn CMyFooTestFixture()
 * \brief constructor 
 * to be used as fixture setup() \n 
 * initialise here all you need in the tests
*/ 
    CMyFooTestFixture()
    {
        // TODO: Common set-up each test case here.

	  user = new User();
    }
  /*! \fn ~CMyFooTestFixture()
 * \brief destructor  
 * to be used as fixture teardown() \n 
 * clean all here
*/ 

    ~CMyFooTestFixture()
    {
        // TODO: Common tear-down for each test case here.
	delete user;
	user=0;
    }
    // TODO: Possibly put some common tests.
    void TestSaveLoad(User& user, bool asBinary)
    {
    }

    // TODO: Declare some common values accesses in tests here.
    User *user;/**< the a object user to be used in each test  */
};

BOOST_FIXTURE_TEST_SUITE(UserTestSuite, CMyFooTestFixture);
BOOST_AUTO_TEST_CASE(readdefaultUserKarma)
{
    BOOST_REQUIRE(user->getKarma());   // Stop here if it fails.
//	BOOST_CHECK_THROW(foo.Save(nullptr), exception);
}

BOOST_AUTO_TEST_CASE(SettingUserName)
{
    user->setName("  foooooo ");
    BOOST_CHECK_EQUAL(user->getName(), "  foooooo ");
}

BOOST_AUTO_TEST_SUITE_END();
