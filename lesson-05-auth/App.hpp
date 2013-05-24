#include <Wt/WApplication>

#include "Session.hpp"

class App : public Wt::WApplication {
private:
    Session session;
    void authEvent();
public:
    App(const Wt::WEnvironment& env, const Services& services);
};
