#include "SayWindow.hpp"
#include "HelloApp.hpp"
#include "Auth/Session.hpp"
#include "models/User.h"
#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WLink>
#include <Wt/WAnchor>
#include <Wt/WTable>
#include <Wt/Dbo/Transaction>

SayWindow::SayWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
     // Get the user's name to say Hi with
     HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
     new Wt::WText(Wt::WString("I have the loggedin user as: ") +app->db().login().user()->Name + app->userName(), this);
          addWidget(new Wt::WBreak());
     new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/ask"), "Go back to ask page", this);
     // Show a list of users
                    addWidget(new Wt::WBreak());
           new Wt::WText(Wt::WString("in database i have to following users:"), this);
                              addWidget(new Wt::WBreak());
                    addWidget(new Wt::WBreak());
     Wt::WTable* table = new Wt::WTable(this);
     Wt::Dbo::Transaction t(app->db());
     Users users = app->userList();
     int i=0;
     for (Users::const_iterator user=users.begin(); user != users.end(); ++user) {
          table->elementAt(i++, 0)->addWidget(
               new Wt::WText(Wt::WString("user [number] is:") +(*user)->getName())
          );
     }
}
