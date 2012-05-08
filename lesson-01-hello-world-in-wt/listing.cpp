/** \file  listing.cpp
*    Description:  using wt:dbo Hello world in c++
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
#include "listing.h"
#include "User.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>

namespace dbo = Wt::Dbo;
using namespace std ;

/*! \fn int createTableForUser(dbo::Session* session)
* \brief Creating the table fo Object User
*
* \param session a handle to a dbo database 
* \return nothing 
*/ 
int createTableForUser(dbo::Session* session)
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
 * \return nothing 
*/ 

int createUserJoe(dbo::Session* session )
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
}
 /*! \fn int readUserAllUser(dbo::Session* session)
 * \brief getting all user from database
 * for each user prints the values
 * \param session a handle to a dbo database 
 * \return nothing 
*/ 

int readUserAllUser(dbo::Session* session)
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
 /*! \fn int main ()
 * \brief a complete database operation
 * create database \n
 * create table for user \n
 * create & store a user \n
 * get and display all User object from database \n
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
readUserAllUser(&session);
}
