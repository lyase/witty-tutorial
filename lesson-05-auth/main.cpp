#include "App.hpp"
#include "Services.hpp"

int main(int argc, char** argv) {

    const Services services;

    auto createApplication = [&](const Wt::WEnvironment& env) { return new App(env, services); };

    return Wt::WRun(argc, argv, createApplication);
}
