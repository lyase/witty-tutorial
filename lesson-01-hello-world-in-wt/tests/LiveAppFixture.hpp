
#ifndef FIXTURE_H
#define  FIXTURE_H


#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <Wt/WWidget>
#include <Wt/WContainerWidget>
#include <Wt/Test/WTestEnvironment>
#include <Wt/WSignal>
#include <Wt/WAnchor>
#include "../HelloApp.hpp"
#include "../MainWindow.hpp"

#include <Wt/Test/WTestEnvironment>
#include "../HelloApp.hpp"
#include "../models/User.h"
#include <Wt/WApplication>

#include <Wt/Test/WTestEnvironment>
#include "../HelloApp.hpp"
#include "../Auth/Services.hpp"
#include "../Auth/Session.hpp"
#include "LiveAppFixture.hpp"
#include <Wt/Dbo/backend/Sqlite3>
#include <boost/filesystem.hpp>
#include <Wt/Test/WTestEnvironment>
class LiveAppFixture {
     Wt::Test::WTestEnvironment* env;
     lesson01Auth::Services* services;
     HelloApp* app;
     LiveAppFixture() ;

     ~LiveAppFixture();

     MainWindow* getMainWindow() ;
};


#endif
