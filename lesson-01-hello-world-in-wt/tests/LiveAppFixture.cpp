
#include "LiveAppFixture.hpp"
LiveAppFixture::LiveAppFixture()
{
     bool createTables=false;
     env= new  Wt::Test::WTestEnvironment("..", "../wt-config.xml");
     services=new  lesson01Auth::Services();
     app=new HelloApp(*env, *services) ;
     app->initialize();
     if (createTables)
          app->session().createTables();
};

// the tearDown
LiveAppFixture::~LiveAppFixture()
{
     app->session().flush();
     boost::filesystem::remove("./blog.db");
     delete env;
     delete services;
     app->quit();
//     delete app;

};
MainWindow* LiveAppFixture::getMainWindow()
{
     // We are getting a handle on the MainWindow
     Wt::WWidget* result = app->root()->widget(0);
     return dynamic_cast<MainWindow*>(result);
}
