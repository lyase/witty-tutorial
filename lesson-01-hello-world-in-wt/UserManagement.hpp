#ifndef USERMANAGEMENT_HPP
#define USERMANAGEMENT_HPP

#include <memory>

class UserManagement {
private:
    class Impl;
    std::unique_ptr<Impl> _impl;
public:
    UserManagement();
    ~UserManagement();
    static UserManagement& instance();
};

#endif // USERMANAGEMENT_HPP
