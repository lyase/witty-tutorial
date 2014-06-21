#include "Session.hpp"
#include "../models/User.h"

#include <Wt/Dbo/Transaction>
#include <Wt/Auth/Identity>
#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Auth/PasswordHash>

namespace Auth {

using namespace Wt;

Session::Session(dbo::SqlConnection& connection, const Services& services)
    : connection_(connection), _services(services)
{
    setConnection(connection_);
    // Map the classes to the DB types
    mapClass<User>("user");
    mapClass<Post>("post");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");
    users_ = new UserDatabase(*this);
    try {
        Wt::Dbo::Transaction t(*this);
        createTables();
        createUser("admin", "admin", "Mister Administrator");
        t.commit();
        std::cerr << "Created database." << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Using existing database";
    }

}

void Session::createUser(const std::string& loginName,
                         const std::string& password,
                         const std::string& fullName)
{
    Wt::Dbo::Transaction t(*this);
    // Create a new Wt user
    Wt::Auth::User user = users_->registerNew();
    // Give him a login name
    user.addIdentity(Wt::Auth::Identity::LoginName, loginName);
    // Set his password
    services().pword.updatePassword(user, password);
    // Create one of our users
    Wt::Dbo::ptr<User> real_user = add(new User());
    real_user.modify()->setName(fullName.empty() ? loginName : fullName);
    // Get the Authentication data
    Wt::Dbo::ptr<AuthInfo> auth_info = users_->find(user);
    // Now hook our user up to the witty user
    auth_info.modify()->setUser(real_user);
    t.commit();
}

dbo::ptr<User> Session::user() const
{
    if (login_.loggedIn()) {
        const Wt::Auth::User& user = login_.user();
        return users_->find(user)->user();
    } else {
        return dbo::ptr<User>();
    }
}

}
