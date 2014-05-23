#include <Wt/WApplication>
#include <Wt/WText>

#include "Session.hpp"

class App : public Wt::WApplication {
private:
     Session session;
     void authEvent();
     Wt::WText* msg;
public:
     App(const Wt::WEnvironment& env, const Services& services);
};
