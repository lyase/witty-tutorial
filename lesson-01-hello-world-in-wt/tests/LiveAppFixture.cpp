
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
     app->quit();
     delete app;
     delete services;
     delete env;
};
MainWindow* LiveAppFixture::getMainWindow()
{
     // We are getting a handle on the MainWindow
     Wt::WWidget* result = app->root()->widget(0);
     return dynamic_cast<MainWindow*>(result);
}
DBCleaner::~DBCleaner()
{
     boost::filesystem::remove("./blog.db");
     // you can put here more cleaning instructions if needed
     //Wt::Test::WTestEnvironment env("..", "../wt-config.xml");
     //HelloApp app(env);
     //    app.db().dropTables();
}
DBCleaner::DBCleaner()
{
     // you can put here cleaning instructions if needed
     // Delete the sqlite db
     boost::filesystem::remove("./blog.db");
}
