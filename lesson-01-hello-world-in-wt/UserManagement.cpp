#include "UserManagement.hpp"
#include "HelloApp.hpp"

UserManagement::UserManagement() {
}

UserMangement& UserManagement::instance() {
    auto app = std::dynamic_cast<HelloApp*>(Wt::WApplication::instance());
    if (app)
        return app->userManagement;
    throw std::logic_error("There should always app");
}
