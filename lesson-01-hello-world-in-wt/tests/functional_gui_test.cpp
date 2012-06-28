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

    LiveAppFixture() : env(".", "wt-config.xml"), app(env) {
        app.initialize();
    }

    MainWindow* getMainWindow() {
        // We are getting a hanfdle on the MainWindow
        Wt::WWidget* result = app.root()->widget(0);
        return dynamic_cast<MainWindow*>(result);
    }
};

BOOST_FIXTURE_TEST_SUITE( FunctionalGuiSuite, LiveAppFixture );

BOOST_AUTO_TEST_CASE( testMainWindowExists ) {
    MainWindow* main = getMainWindow();
    BOOST_REQUIRE(main);
}

BOOST_AUTO_TEST_CASE( testAskLink ) {
    MainWindow* main = getMainWindow();
    BOOST_REQUIRE(main);
    Wt::WMouseEvent click;
    BOOST_REQUIRE( app.internalPath() != "/ask" );
    main->_askLink->clicked().emit(click);
    BOOST_CHECK_EQUAL( app.internalPath(), "/ask" );
}

BOOST_AUTO_TEST_SUITE_END();
