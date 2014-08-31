#pragma once
#include <Wt/Auth/AuthService>
#include <Wt/Auth/PasswordService>

namespace lesson01Auth {

class Services {
private:
    static Services* _instance;
public:
     Wt::Auth::AuthService auth;
     Wt::Auth::PasswordService pword;
     Services();
     Services* instance();
};

}
