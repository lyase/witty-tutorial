
#ifndef FIXTURE_H
#define  FIXTURE_H
#include "../Auth/Services.hpp"
#include "../Auth/Session.hpp"
#include "../HelloApp.hpp"
#include "../MainWindow.hpp"
#include "../models/User.h"
#include "LiveAppFixture.hpp"
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Test/WTestEnvironment>
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WWidget>
#include <boost/filesystem.hpp>
#include <boost/test/test_tools.hpp>
class LiveAppFixture {
private:
     Wt::Test::WTestEnvironment* env;
     lesson01Auth::Services* services;
     HelloApp* app;
     LiveAppFixture() ;

     ~LiveAppFixture();

     MainWindow* getMainWindow() ;
};


#endif
