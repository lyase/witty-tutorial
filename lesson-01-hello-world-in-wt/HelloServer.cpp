#include "HelloServer.hpp"
#include <stdexcept>


HelloServer::HelloServer(
    const std::string &wtApplicationPath,
    const std::string &wtConfigurationFile)
    : WServer(wtApplicationPath, wtConfigurationFile) {
    _auth.setAuthTokensEnabled(true, "hello-auth");
    _auth.setTokenHashFunction(&_hashFunction);
    _auth.setIdentityPolicy(Wt::Auth::LoginNameIdentity);
    if (!Wt::Auth::FacebookService::configured())
        throw std::logic_error("Facebook Auth not configured - not starting app");
    _facebookAuth.reset(new Wt::Auth::FacebookService(_auth));
}
