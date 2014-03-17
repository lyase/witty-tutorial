#pragma once
#include <Wt/Auth/AuthService>
#include <Wt/Auth/PasswordService>

struct Services {
     Wt::Auth::AuthService auth;
     Wt::Auth::PasswordService pword;
     Services();
};
