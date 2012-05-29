/** \file  testUser_Class_dbo.cpp
*    Description:  minimal application using dbo for User class from :
* http://www.webtoolkit.eu/wt/doc/tutorial/dbo.html
*shows how to use dbo functionality with User class

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
/*
   * note Try to create the schema (will fail if already exists delete database first).
   */
 /*! \fn int main ()
 * \brief a complete database operation
 * create database \n
 * create table for user \n
 * create & store a user \n
 * get and display all User object from database \n
 * * update   karma field of user Joe\n
  * get and display updated  User Joe object from database \n
  * delete user joe from database \n
 * \return nothing
*/

int main ()
{
cout<<" Create database connection \n";
dbo::backend::Sqlite3 sqlite3("blog.db");
dbo::Session session;
session.setConnection(sqlite3);
createTableForUser(&session);
createUserJoe(&session);
readUserJoe(&session);
cout <<" updating user joe ";
readUserJoeOnly(&session);
cout <<" updating user joe ";
updateUserJoeOnly(&session);
cout <<" printing updated  user joe ";
readUserJoeOnly(&session);
cout<< "deleting user joe";
deleteUserJoeOnly(&session);
readUserJoe(&session);
}
