#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/Test/WTestEnvironment>
#include <Wt/WSignal>
#include <Wt/WAnchor>
#include "../HelloApp.hpp"
#include "../MainWindow.hpp"

struct LiveAppFixture {
    Wt::Test::WTestEnvironment env;
    HelloApp app;
// put here your setUp for the tests
    LiveAppFixture() : env(".", "wt-config.xml"), app(env) {
        app.initialize();
	
    }
    // the tearDown
    ~LiveAppFixture(){
    }
    MainWindow* getMainWindow() {
        // We are getting a handle on the MainWindow
        Wt::WWidget* result = app.root()->widget(0);
        return dynamic_cast<MainWindow*>(result);
    }
};
// we are testing here:
//if the app can create  it's landing page 
BOOST_FIXTURE_TEST_SUITE( FunctionalGuiSuite, LiveAppFixture );

BOOST_AUTO_TEST_CASE( testMainWindowExists ) {
    MainWindow* main = getMainWindow();
    BOOST_REQUIRE(main);
}
// we are testing here: 
//clicking the link to ask page  from the  landing page we
//can  will change the path to the ask window
BOOST_AUTO_TEST_CASE( testAskLink ) {
    MainWindow* main = getMainWindow();
    BOOST_REQUIRE(main);
    Wt::WMouseEvent click;
    cout<<"before click path is "<< app.internalPath() << endl;
    BOOST_REQUIRE( app.internalPath() != "/ask" );
    main->_askLink->clicked().emit(click);
    BOOST_CHECK_EQUAL( app.internalPath(), "/ask" );

}

BOOST_AUTO_TEST_SUITE_END();
