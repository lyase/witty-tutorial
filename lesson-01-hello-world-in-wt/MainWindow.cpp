#include "MainWindow.hpp"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WString>
#include <Wt/WLink>
#include <Wt/WAnchor>
#include <Wt/WApplication>

#include "HelloApp.hpp"

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
     _inputLabel = new Wt::WLabel("What is your name?", this);
     addWidget(new Wt::WBreak());
     _nameInput = new Wt::WLineEdit(this);
     _nameInput->setFocus();
     _inputLabel->setBuddy(_nameInput);
     addWidget(new Wt::WBreak());
     _btnHi = new Wt::WPushButton("Say Hi", this);
     addWidget(new Wt::WBreak());
     _nameOutput = new Wt::WText(this);
     addWidget(new Wt::WBreak());
     _btnHi->clicked().connect(this, &MainWindow::sayHi);
     // because of the following  you need to delete user memory del user in destructor to prevent memory leak
     user = new User();
     addWidget(new Wt::WBreak());
     _askLink = new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/ask"), "Register User", this);
     addWidget(new Wt::WBreak());
     _adminLink = new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/admin"), "go to app admin ", this);

     HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
     new Wt::WAnchor(app->calc, "Calculator", this);

}
void MainWindow::sayHi()
{
     user->setName(_nameInput->valueText().toUTF8());
     if( (user->getName()=="") or(user->getName()=="Joe")) {
          user->setName(" visiteur inconnu");
     } else {
          _nameOutput->setText("Hi there " + user->getName());
     }
}
