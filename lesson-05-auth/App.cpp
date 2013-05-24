#include "App.hpp"
#include <Wt/WText>
#include <Wt/Auth/AuthWidget>

App::App(const Wt::WEnvironment& env, const Services& services)
     : Wt::WApplication(env), session(appRoot() + "myapp.db", services)
{
    session.login().changed().connect(this, &App::authEvent);
    new Wt::WText("Hello", root());
    auto authWidget = new Wt::Auth::AuthWidget(services.auth, session.users(), session.login());
    root()->addWidget(authWidget);
    authWidget->model()->addPasswordAuth(services.pword);
    authWidget->setRegistrationEnabled(true);
    authWidget->processEnvironment();
}

void App::authEvent () {

}
