/** \file  listing.cpp
*    Description:  implementing CRUD function for USER  class using wt:dbo Hello world in c++
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
#include "listing.h"
#include "User.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>

namespace dbo = Wt::Dbo;
using namespace std ;
void createTableForUser(dbo::Session* session)
{
    cout<<" Create table for user\n" ;
dbo::Transaction transaction(*session);
session->mapClass<User>("user");

  /*
   * Try to create the schema (will fail if already exists).
   */
  session->createTables();
  transaction.commit();
}
 /*! \fn int createUserJoe(dbo::Session* session )
 * \brief Creating the user and save object to database
 *
 * \param session a handle to a dbo database 
*example creating the session object \n
*cout<<" Create database connection \n";\n
*dbo::backend::Sqlite3 sqlite3("blog.db");\n
*dbo::Session session;\n
*createUserJoe(&session);

 * \return nothing 
*/ 

void createUserJoe(dbo::Session* session )
{
dbo::Transaction transaction(*session);  
  cout<<" Create  a userJoe\n ";
  User *user;
  user = new User();
  user->setName("Joe");
  user->setPassword("Secret");
  user->setRole(Visitor);
  user->setKarma(13);

  cout<<" Adding  user to database \n ";
  dbo::ptr<User> userPtr = session->add(user);

  cout<<" Commit to database \n ";
  transaction.commit();
 // delete  user;
 // user=0;
}
 /*! \fn int readUserAllUser(dbo::Session* session)
 * \brief getting all user from database
 * for each user prints the values
 * \param session a handle to a dbo database 
*example creating the session object \n
*cout<<" Create database connection \n";\n
*dbo::backend::Sqlite3 sqlite3("blog.db");\n
*dbo::Session session;\n
*readUserAllUser(&session);
* \return nothing 
*/ 

void  readUserAllUser(dbo::Session* session)
{
cout<<" Reading user \n ";
dbo::Transaction transaction(*session);
  // now getting all user objects you may use filter like 
// Wt::Dbo::ptr<User> bart = session.find<User>().where("name = ?").bind("Bart");
// but does not work with all wt version
cout<<" looking for all user objects\n";
Users users = session->find<User>();

cerr << "We have " << users.size() << " users:" << std::endl;
cerr <<"listing the user i found in database"<<std::endl ; 
for (Users::const_iterator i = users.begin(); i != users.end(); ++i)
        cerr << " user " << (*i)->getName()
              << " with karma of " << (*i)->getKarma() << endl
              << " with Role of " << (*i)->getRole() << endl;
  transaction.commit();
}
void readUserJoe(dbo::Session* session)
{
  cout<<" Reading user \n ";
/*    cout<<" i will create database connection to read\n";
dbo::backend::Sqlite3 sqlite3("blog.db");
dbo::Session session;
session.setConnection(sqlite3);
*/
dbo::Transaction transaction(*session);
//session->mapClass<User>("user");
  // now finding an object 
cout<<" looking for  user objects\n";
Users users = session->find<User>();

cerr << "We have " << users.size() << " users:" << std::endl;

for (Users::const_iterator i = users.begin(); i != users.end(); ++i)
        cerr << " user " << (*i)->getName()
              << " with karma of " << (*i)->getKarma() << endl
              << " with Role of " << (*i)->getRole() << endl;
  transaction.commit();
}
/*
   * Try to create the schema (will fail if already exists).
   */
 /*! \fn int main ()
 * \brief a complete database operation
 * create database \n
 * create table for user \n
 * create & store a user \n
 * get and display all User object from database \n
 * \return nothing 
*/ 
