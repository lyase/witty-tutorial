/** \file  testUser_Class.cpp
* \brief    Description:  tests(boost framework) for class User
*checking functionality and documenting basic usage of User class you will find dbo example 
*\b this compiles & run  with : \code // rename testUser_Class.cpp User.hpp->testUser_Class.cpp g++ -g -lboost_unit_test_framework  -o tests testUser_Class.cpp User.cpp&&./tests --log_level=test_suite --report_level=short \endcode
to get xml result We run our tests with \code// ./test --report_format=xml --report_level=detailed --log_level=test_suite --log_format=xml \endcode . You need both stderr and stdout, then we replace <TestLog> with <xml><TestLog> and replace </TestResult> with </TestResult><xml>. After that we run it though tidy and finally run that though this xslt.

./tests --log_format=XML --report_level=detailed 
or see http://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/parameters/index.html for more options


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
#include <boost/filesystem.hpp>
using namespace std ;
/** a structure used to have fixture for the  tests \n 
*the constructor will be called before each test should be used  as the setup() \n
*the destructor will be called after every test should be used as teardown().
*/

struct CMyFooTestFixture
{
/*! \fn CMyFooTestFixture()
* \brief constructor 
* to be used as fixture setup() \n 
* initialise here all you need for  the tests
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
        // TODO: Common tear-down after  each test case here.
	delete user;
	user=0;
    // Delete the sqlite db
    boost::filesystem::remove("./blog.db");

    }
    // TODO: Possibly put some function common to  tests.
    void TestSaveLoad(User& user, bool asBinary)
    {
    }

    // TODO: Declare some common values accesses in tests here.
    User *user;/**< the a object user to be used in each test  */
};

BOOST_FIXTURE_TEST_SUITE(UserTestSuite, CMyFooTestFixture);
BOOST_AUTO_TEST_CASE(readdefaultUserKarma)
{
/*! 
* will test a user has a karma
*
*/
    BOOST_REQUIRE(user->getKarma());   // Stop here if it fails.
//	BOOST_CHECK_THROW(foo.Save(nullptr), exception); would be an alternative if you want to continue testing even after exception in test
}
/*! 
* will test a user can get a new name
*
*/
BOOST_AUTO_TEST_CASE(SettingUserName)
{
    user->setName("  foooooo ");
    BOOST_CHECK_EQUAL(user->getName(), "  foooooo ");
}

BOOST_AUTO_TEST_SUITE_END();
