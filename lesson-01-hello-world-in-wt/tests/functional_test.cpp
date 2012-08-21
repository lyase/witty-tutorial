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

struct LiveAppFixture {
    Wt::Test::WTestEnvironment env;
    HelloApp app;
// put here your setUp for the tests
    LiveAppFixture() : env(".", "wt-config.xml"), app(env) {
        app.initialize();
    }
    // the tearDown
    ~LiveAppFixture() {
    }
    MainWindow* getMainWindow() {
        // We are getting a handle on the MainWindow
        Wt::WWidget* result = app.root()->widget(0);
        return dynamic_cast<MainWindow*>(result);
    }
};


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



BOOST_AUTO_TEST_SUITE_END();
