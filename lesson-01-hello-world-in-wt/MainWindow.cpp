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
#include <Wt/Auth/AuthWidget>

#include "HelloApp.hpp"
#include "Auth/Services.hpp"

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
    HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
    ::Auth::Session& session = app->session();
    loginStatus_ = new Wt::Auth::AuthWidget(lesson01Auth::Services::instance()->auth, session.users(), session.login(), this);
    loginStatus_->setRegistrationEnabled(true);
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
    user.reset(new User());
    addWidget(new Wt::WBreak());
    _askLink = new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/ask"), "Create  User Account", this);
    addWidget(new Wt::WBreak());
    _adminLink = new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/admin"), "go to app admin ", this);
    _sayLink = new Wt::WAnchor(Wt::WLink(Wt::WLink::InternalPath, "/say"), "User List page:", this);
    addWidget(new Wt::WBreak());
    new Wt::WAnchor(app->calc, "go calc xml ressource", this);
    session.login().changed().connect(this, &MainWindow::onUserChanged);

    addWidget(new Wt::WBreak());
    Wt::WPushButton* reg = new Wt::WPushButton("Register as a new user", this);
    reg->clicked().connect(loginStatus_, &Wt::Auth::AuthWidget::registerNewUser);

//     loginWidget_ = new BlogLoginWidget(session_, basePath);

}
void MainWindow::sayHi()
{
    user->setName(_nameInput->valueText().toUTF8());
    if( (user->getName()=="") or(user->getName()=="Joe")) {
        user->setName(" visiteur inconnu");
    } else {
        _nameOutput->setText("in page message on button click I say Hi there " + user->getName());
    }
}
const Wt::WString& MainWindow::getLastName()
{
    return _lastNameEntered;
}
void MainWindow::onUserChanged()
{
    HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
    if (app->session().login().loggedIn())
        loggedIn();
    //else
    //loggedOut(); // TODO: add an event handler for when the user logs out
}
void MainWindow::loggedIn()
{
    Wt::WApplication::instance()->changeSessionId();

    //refresh(); // TODO: Refresh the display for the new user

    Wt::WText *profileLink = new Wt::WText(tr("profile"));
    profileLink->setStyleClass("link");
    //profileLink->clicked().connect(this, &BlogImpl::editProfile); // TODO: Import profile editor

    HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
    dbo::ptr<User> user = app->session().user();

    if (user->getRole() == Admin) {
        Wt::WText *editUsersLink = new Wt::WText(tr("edit-users"));
        editUsersLink->setStyleClass("link");
        //editUsersLink->clicked().connect(SLOT(this, BlogImpl::editUsers));
        //loginStatus_->bindWidget("userlist-link", editUsersLink);
        Wt::WText *authorPanelLink = new Wt::WText(tr("author-post"));
        authorPanelLink->setStyleClass("link");
        //authorPanelLink->clicked().connect(SLOT(this, BlogImpl::authorPanel));
        //loginStatus_->bindWidget("author-panel-link", authorPanelLink);
    } else {
        //loginStatus_->bindEmpty("userlist-link");
        //loginStatus_->bindEmpty("author-panel-link");
    }

    //loginStatus_->bindWidget("profile-link", profileLink);

    //bindPanelTemplates();
}
