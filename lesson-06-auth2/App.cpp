#include "App.hpp"
#include <Wt/Auth/AuthWidget>
#include <Wt/Dbo/Transaction>
#include <Wt/WContainerWidget>

namespace dbo = Wt::Dbo;

App::App(const Wt::WEnvironment& env, const Services& services)
     : Wt::WApplication(env), session(appRoot() + "myapp.db", services)
{
    msg = new Wt::WText(root());
    msg->setText("created a default user in database when initialized</BR> you can log with admin/admin");
    session.login().changed().connect(this, &App::authEvent);
    // Show the login form
    auto authWidget = new Wt::Auth::AuthWidget(services.auth, session.users(), session.login());
    root()->addWidget(authWidget);
    authWidget->model()->addPasswordAuth(&services.pword);
    authWidget->setRegistrationEnabled(true);
    authWidget->processEnvironment();
}

void App::authEvent () {
    auto user = session.login().user();
    if (user.isValid()) {
        // Say hello to the logged in user
        auto auth_info = session.users().find(user);
        dbo::Transaction t(session);
        auto real_user = auth_info->user();
        Wt::WString txt("Hello {1}. I see that you are {2} years old");
        msg->setText(txt.arg(real_user->name).arg(real_user->age));
    } else {
        msg->setText("Nobody is logged in");
    }
}
