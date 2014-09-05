#include "Services.hpp"
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/PasswordVerifier>

namespace lesson01Auth {

// Initialize the static Singleton
Services* Services::_instance = NULL;

Services::Services() : auth(), pword(auth)
{
    assert(!_instance); // There can be only one!
    _instance = this;
     auth.setAuthTokensEnabled(true, "my-auth-token");
     auth.setEmailVerificationEnabled(true);
     auth.setIdentityPolicy(Wt::Auth::LoginNameIdentity);

     Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
     verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
     pword.setVerifier(verifier);
     pword.setAttemptThrottlingEnabled(true);
     pword.setStrengthValidator(new Wt::Auth::PasswordStrengthValidator());
}

Services::~Services () {
    _instance = 0;
}

const Services* Services::instance() {
    assert(_instance); // If someone calls this, it had better exist
    return _instance;
}

}
