#include "Services.hpp"

#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/PasswordVerifier>

namespace Auth {

Services::Services() : auth(), pword(auth) {
    auth.setAuthTokensEnabled(true, "my-auth-token");
    auth.setEmailVerificationEnabled(true);

    Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
    verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
    pword.setVerifier(verifier);
    pword.setAttemptThrottlingEnabled(true);
    pword.setStrengthValidator(new Wt::Auth::PasswordStrengthValidator());
}

}
