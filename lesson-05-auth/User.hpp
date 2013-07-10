#pragma once
#include <Wt/Dbo/Dbo>

namespace dbo = Wt::Dbo;

class User;
typedef Wt::Auth::Dbo::AuthInfo<User> AuthInfo;

class User {
public:
    int age;
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, age, "age");
    }
};
