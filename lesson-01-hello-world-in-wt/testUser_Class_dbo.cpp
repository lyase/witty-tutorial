/** \file  testUser_Class_dbo.cpp
*    Description:  minimal application using dbo for User class 
*shows how to use dbo functionality of User class 

*\b compiles with \code g++listing.cpp User.cpp testUser_Class_dbo.cpp -o testdbo -l wtdbosqlite3 \endcode
*\b run with 
*\code  rm blog.db ; ./testdbo \endcode
*\n
*\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */#include <Wt/Dbo/Dbo>
#include "listing.h"
#include "User.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
int main ()
{
cout<<" Create database connection \n";
dbo::backend::Sqlite3 sqlite3("blog.db");
dbo::Session session;
session.setConnection(sqlite3);
createTableForUser(&session);
createUserJoe(&session);
readUserJoe(&session);
}
