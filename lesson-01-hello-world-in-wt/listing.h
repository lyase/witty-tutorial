/** \file  liingst.h
*    header for minimal dbo app
*\b compiles with \code g++ listing.cpp User.cpp -o test -l wtdbosqlite3 \endcode
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
#include "User.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
// compile with g++ listing.cpp -o test -l wtdbosqlite3

namespace dbo = Wt::Dbo;
using namespace std ;

int createTableForUser (dbo::Session*);
int createDatabase(dbo::Session*);
int createUserJoe(dbo::Session*);
int readUserJoe(dbo::Session* );

int main ();
