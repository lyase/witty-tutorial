/** \file  listing.h
*    Description:  header for CRUD function for USER  class using wt:dbo Hello world in c++
*\b compiles with \code g++listing.cpp User.cpp testUser_Class_dbo.cpp -o test -l wtdbosqlite3 \endcode
*\n
*then run with
*\code  ./test \endcode
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:
 *
 * =====================================================================================
 */
#include <Wt/Dbo/Dbo>
#include "models/User.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
// compile with g++ listing.cpp -o test -l wtdbosqlite3

namespace dbo = Wt::Dbo;
using namespace std ;
/*!
* \fn void createTableForUser(dbo::Session* session)
*\brief Creating the table fo Object User \n
*\param session a handle to a dbo database
*\return nothing
*/
void createTableForUser (dbo::Session*);
void createDatabase(dbo::Session*);
void  createUserJoe(dbo::Session*);
void  readUserAllUser(dbo::Session* );
void readUserJoe(dbo::Session* session);
void readUserJoeOnly(dbo::Session* session);
void read_UnknownUserthrowsexception(dbo::Session* session);
void updateUserJoeOnly(dbo::Session* session);
void deleteUserJoeOnly(dbo::Session* session);
int main ();
