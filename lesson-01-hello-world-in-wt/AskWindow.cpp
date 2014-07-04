#include "AskWindow.hpp"
#include "HelloApp.hpp"
#include "Auth/Session.hpp"
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WApplication>
#include <Wt/WMessageBox>

AskWindow::AskWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
     _inputLabel = new Wt::WLabel("New User name", this);
     _nameInput = new Wt::WLineEdit(this);
     _nameInput->setFocus();
     _inputLabel->setBuddy(_nameInput);

     Wt::WLabel* pwordLabel = new Wt::WLabel("New Password", this);
     _pwordInput = new Wt::WLineEdit(this);
     pwordLabel->setBuddy(_nameInput);

     _btnCreateUser = new Wt::WPushButton("Create User", this);
     _nameOutput = new Wt::WText(this);
     _btnCreateUser->clicked().connect(this, &AskWindow::sayHi);
}

void AskWindow::sayHi()
{
     Wt::WString name = _nameInput->valueText();
     Wt::WString pword = _pwordInput->valueText();
     HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
     app->session().createUser(name.toUTF8(), pword.toUTF8());
     Wt::WMessageBox::show("User Created",
                           std::string("Created User: ") + name,
                           Wt::Ok);

}
