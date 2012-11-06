#include "UserManagement.hpp"
#include "HelloApp.hpp"
#include "User.h"

class UserManagement::Impl {
};

UserManagement::UserManagement() : _impl{new Impl{}} {

}

UserManagement::~UserManagement() {
    // Needs to be here so that the pimpl destructor knows how big the thing it's destructing is
    // See: http://herbsutter.com/gotw/_100/
}

UserManagement& UserManagement::instance() {
    HelloApp* app = dynamic_cast<HelloApp*>(Wt::WApplication::instance());
    if (app)
        return app->users;
    throw std::logic_error("There should always app");
}
