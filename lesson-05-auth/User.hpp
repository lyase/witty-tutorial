#pragma once
#include <Wt/Dbo/Dbo>

#include <string>

namespace dbo = Wt::Dbo;

class User;
typedef Wt::Auth::Dbo::AuthInfo<User> AuthInfo;

class User {
public:
    int age;
    std::string name;
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, age, "age");
        dbo::field(a, name, "name");
    }
};
