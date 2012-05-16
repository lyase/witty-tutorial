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
MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    _inputLabel = new Wt::WLabel("What is your name?", this);
    _nameInput = new Wt::WLineEdit(this);
    _nameInput->setFocus();
    _inputLabel->setBuddy(_nameInput);
    _btnHi = new Wt::WPushButton("Say Hi", this);
         _nameOutput = new Wt::WText(this);
    _btnHi->clicked().connect(this, &MainWindow::sayHi);
// because of the following  you need to delete user memory del user in destructor to prevent memory leak
  user = new User();
  std::string buildinfo;
  buildinfo=" i was in ";
#define WRNG_PRIVATE_STR2(z) #z
#define WRNG_PRIVATE_STR1(x) WRNG_PRIVATE_STR2(x)
#define WRNG __FILE__ "Compiled at:("WRNG_PRIVATE_STR1(__TIME__)")line:("WRNG_PRIVATE_STR1(__LINE__)"): ------------ : "

//#define WRNG __FILE__ "("WRNG_PRIVATE_STR1(__LINE__)"): ------------ : "
buildinfo+=WRNG ;
    new Wt::WAnchor(Wt::WLink("/docs.html"), "Show Docs"+buildinfo, this);
}
void MainWindow::sayHi() {
    user->setName(_nameInput->valueText().toUTF8());
    if( (user->getName()=="") or(user->getName()=="Joe")) 
        user->setName(" visiteur inconnu");
    else
        _nameOutput->setText("Hi there " + user->getName());
}
