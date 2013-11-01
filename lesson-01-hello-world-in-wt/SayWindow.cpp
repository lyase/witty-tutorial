#include "SayWindow.hpp"
#include "HelloApp.hpp"
#include "Auth/Session.hpp"
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
     new Wt::WText(Wt::WString("Hi ") + app->userName(), this);
     new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/ask"), "Go back to ask page", this);
     // Show a list of users
     auto table = new Wt::WTable(this);
     Wt::Dbo::Transaction t(app->db());
     auto users = app->userList();
     int i=0;
for (auto user : users)
          table->elementAt(i++, 0)->addWidget(
               new Wt::WText(user->getName())
          );
}
