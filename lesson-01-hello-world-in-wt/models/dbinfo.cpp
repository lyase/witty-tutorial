#include "dbinfo.hpp"

DBInfo::DBInfo(Wt::WObject* parent, const std::string& dbConnString, const lesson01Auth::Services& services) :
     Wt::WObject(parent), connection(dbConnString), session(connection, services)
{
     session.setConnection(connection);
}
