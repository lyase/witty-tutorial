/** \file  testUser_Class_dbo.cpp
*    Description:  tests(boost framework)
*shows how to use dbo functionality of User class 

*\b compiles & run  with : \code //g++ testUser_Class_dbo.cpp User.cpp -o testdbo -l wtdbosqlite3;
 rm blog.db ; ./testdbo \endcode
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
// compile with g++ listing.cpp -o test -l wtdbosqlite3
//g++ listing.cpp User.cpp -o test -l wtdbosqlite3


namespace dbo = Wt::Dbo;
using namespace std ;


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

int createUserJoe(dbo::Session* session )
{

dbo::Transaction transaction(*session);
// creating a user and saving to database
   
//session->mapClass<User>("user");
  
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
//  delete  user;
//  user=0;
  }



int readUserJoe(dbo::Session* session)
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