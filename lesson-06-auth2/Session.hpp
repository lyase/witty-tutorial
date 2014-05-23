#pragma once
#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Auth/Login>
#include <Wt/Auth/Dbo/UserDatabase>
#include <Wt/Dbo/SqlConnection>
#include "User.hpp"
#include "Services.hpp"

namespace dbo = Wt::Dbo;

typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

class Session : public dbo::Session {
private:
     dbo::backend::Sqlite3 connection_;
     UserDatabase *users_;
     Wt::Auth::Login login_;
     const Services& _services;
public:
     Session(const std::string& sqliteDbFileName, const Services& services);

     UserDatabase& users() {
          return *users_;
     }
     Wt::Auth::Login& login() {
          return login_;
     }
     const Services& services() {
          return _services;
     }
};
