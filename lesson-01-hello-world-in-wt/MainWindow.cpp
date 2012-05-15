#include "MainWindow.hpp"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    _inputLabel = new Wt::WLabel("What is your name?", this);
    _nameInput = new Wt::WLineEdit(this);
    _nameInput->setFocus();
    _inputLabel->setBuddy(_nameInput);
    _btnHi = new Wt::WPushButton("Say Hi", this);

    _btnHi->clicked().connect(this, &MainWindow::sayHi);
// because of the following  you need to delete user memory del user in destructor to prevent memory leak
  user = new User();
}

void MainWindow::sayHi() {
    user->setName(_nameInput->valueText().toUTF8());
    if( (user->getName()=="") or(user->getName()=="Joe")) 
        user->setName(" visiteur inconnu");
    else
        _nameOutput->setText("Hi there " + user->getName());
}
