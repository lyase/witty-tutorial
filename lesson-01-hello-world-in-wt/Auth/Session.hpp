#pragma once
#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Auth/Login>
#include <Wt/Auth/Dbo/UserDatabase>

#include "../models/User.h"
#include "Services.hpp"

namespace Auth {

namespace dbo = Wt::Dbo;

typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

class Session : public dbo::Session {
private:
     dbo::SqlConnection& connection_;
     UserDatabase *users_;
     Wt::Auth::Login login_;
     const Services& _services;
public:
     Session(dbo::SqlConnection& connection, const Services& services);

     UserDatabase& users() {
          return *users_;
     }
     Wt::Auth::Login& login() {
          return login_;
     }
     const Services& services() {
          return _services;
     }
     void createUser(const std::string& loginName,
                     const std::string& password,
                     const std::string& fullName="");
};

}
