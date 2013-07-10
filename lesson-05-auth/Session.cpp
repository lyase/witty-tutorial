#include "Session.hpp"
#include "User.hpp"

#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>

using namespace Wt;

Session::Session(const std::string& sqliteDb, const Services& services)
  : connection_(sqliteDb), _services(services) {
    setConnection(connection_);

    // Map the classes to the DB types
    mapClass<User>("user");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");

    try {
        createTables();
        std::cerr << "Created database." << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Using existing database";
    }

    users_ = new UserDatabase(*this);
}
