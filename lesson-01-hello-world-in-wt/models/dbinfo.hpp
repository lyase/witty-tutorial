#ifndef DBINFO_HPP
#define DBINFO_HPP
#include <Wt/WServer>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Exception>
#include <Wt/Dbo/collection>
#include <Wt/WCssTheme>
#include "../Auth/Session.hpp"
#include "../Auth/Services.hpp"
/*! A DBInfo   class
* \details This class will handle a dbo session
* this class has dbo support example of Many-to-One relations with user.
* \author Lyase damasked from wt/dbo/tutorial.html
* \version 4.1a
* \date 1990-2012
* \pre First initialize the system.
* \bug .
*
*/
/*! \brief  this class handles   of the application dbo parameters & dbo ssession
     */
class DBInfo : public Wt::WObject {
private:

public:
     Wt::Dbo::backend::Sqlite3 connection;
     ::Auth::Session session;

     DBInfo(Wt::WObject* parent, const std::string& dbConnString, const lesson01Auth::Services& services) ;
};

#endif // DBINFO_HPP
