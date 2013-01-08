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
#include <Wt/Dbo/Exception>
namespace dbo = Wt::Dbo;
using namespace std ;
/*! \fn void createTableForUser(dbo::Session* session)
      * this should be run before any object is saved to database
            note you need to create all tables for all Object don't assume children classes will be created
             * @brief pre-condition to CRUD operation
              *
               * @param session
                */
void createTableForUser(dbo::Session* session)
{
    cout<<" Create table \n" ;
    dbo::Transaction transaction(*session);
    cout<<" Create table for post\n" ;
    session->mapClass<Post>("post");
    cout<<" Create table for user\n" ;
    session->mapClass<User>("user");


    /*
     * Try to create the schema (will fail if already exists).
     */
    try {
        session->createTables();
    } catch (Wt::Dbo::Exception e) {
        cout <<"in createTables() caught a Wt::Dbo::Exception:/ "<<e.what()<<"/ could not createTableForUser check blog.db is empty\n";
    }
    try {
        transaction.commit();
    } catch (Wt::Dbo::Exception e) {
        cout <<"in commit() caught a Wt::Dbo::Exception:/ "<<e.what()<<"/ could not createTableForUser check blog.db is empty\n";
    }
}
/*! \fn int createUserJoe(dbo::Session* session )
* \brief Creating the user and a Post  and save objects to database
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
    // try {
    dbo::Transaction transaction(*session);
    cout<<" Create  a userJoe\n ";
    User *user;
    user = new User();
    cout<<" Adding  user to database \n ";
    dbo::ptr<User> userPtr = session->add(user);
    cout<<" Adding  post  to database \n ";
    dbo::ptr<Post> post = session->add(new Post());
    user->posts.insert(post);
    //    post.modify()->author = userPtr;  // will segfault
    //    post.modify()->author = user;  // will segfault

    cout << "Joe has " << user->posts.size() << " post(s)." << std::endl;
    user->setName("Joe");
    user->setPassword("Secret");
    user->setRole(Visitor);
    user->setKarma(13);

    //cout<<" Adding  user to database \n ";
    //dbo::ptr<User> userPtr = session->add(user);
    //opposite operation is ptr<Dbo>::remove(): it deletes
    cout<<" trying Commit to database \n ";
    try {
        transaction.commit();
    } catch (Wt::Dbo::Exception e) {
        cout <<"in createUserJoe commit () caught a Wt::Dbo::Exception:/ "<<e.what()<<"/\n";
    }
    //carefull this final cleanup will crash app
    //delete  user;
    //user=0;
    // looks like i am not catching all possible exception here so commented for now} catch (Wt::Dbo::Exception e) {
    //                                 cout <<"in createUserJoe() caught a Wt::Dbo::Exception:/ "<<e.what()<<"/\n";
    //                                 }
    //note this function can segfault ie i am not catching all exceptions
    //delete  user;
    //user=0;
}
/*! \fn void readUserAllUser(dbo::Session* session)
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
    cerr <<"listing the user I found in database"<<std::endl ;
    for (Users::const_iterator i = users.begin(); i != users.end(); ++i)
        cerr << " user " << (*i)->getName()
             << " with karma of " << (*i)->getKarma() << endl
             << " with Role of " << (*i)->getRole() << endl
             << "this user  has " << (*i)->posts.size() << " post(s)." << std::endl;
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
             << " with Role of " << (*i)->getRole() << endl
             << " with number of Post: " << (*i)->posts.size() << " post(s)." << std::endl;
    transaction.commit();
}
/*! \fn void readUserJoeOnly(dbo::Session* session)
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
void readUserJoeOnly(dbo::Session* session)
{
    cout<<" start transaction \n ";

    dbo::Transaction transaction(*session);
    cout<<" looking for  user Joe in database may throw exception if not found " <<std::endl;
    // bind parameter this way does not work with all wt version
    dbo::ptr<User> joe = session->find<User>().where("name = ?").bind("Joe");
    int count = session->query<int>("select count(1) from user").where("name = ?").bind("Joe");
    if(joe& count==1) {
        cout <<"we found 1 user joe"<< std::endl;

        cout << "here is  Joe:" << std::endl;
        cout << " user name: " << joe->getName()
             << " with karma of " << joe->getKarma() << endl
             << " with Role of " << joe->getRole() << endl
             <<"   this user has:"<<  joe->posts.size() << " post(s)." << std::endl;
    }
}
/*! \fn void read_UnknownUserthrowsexception(dbo::Session* session)
* \brief getting read_UnknownUserthrowsexception from database
* this should fail and throw an exception
* \param session a handle to a dbo database
*example creating the session object \n
*cout<<" Create database connection \n";\n
*dbo::backend::Sqlite3 sqlite3("blog.db");\n
*dbo::Session session;\n
*readUserAllUser(&session);
* \return nothing
*/
void read_UnknownUserthrowsexception(dbo::Session* session)
{
    cout<<" start transaction \n ";

    dbo::Transaction transaction(*session);

    // bind parameter this way does not work with all wt version no exception thrown  if not found but (joe.get() == 0)
    dbo::ptr<User> joe = session->find<User>().where("name = ?").bind("unknown");
    int count = session->query<int>("select count(1) from user").where("name = ?").bind("unknown");
    cout <<"we found "<<count <<" user unknow"<< std::endl;
    if((joe.get() == 0) & count==0)

    {
        cout <<"GOOD we found 0 user unknow and joe is empty"<< std::endl;
    }
    cout <<" done i am closing transaction"<< std::endl;
    transaction.commit();
}

/*! \fn void updateUserJoeOnly(dbo::Session* session)
* \brief getting all user from database
* for each user prints the values
* \param session a handle to a dbo database
*example creating the session object \n
*cout<<" Create database connection \n";\n
*dbo::backend::Sqlite3 sqlite3("blog.db");\n
*dbo::Session session;\n

* \return nothing
*/
void updateUserJoeOnly(dbo::Session* session)
{
    cout<<" start transaction to update values of user joe  "<< std::endl;

    dbo::Transaction transaction(*session);
    cout<<" looking for  user Joe in database may throw exception if not found " <<std::endl;
    int count = session->query<int>("select count(1) from user").where("name = ?").bind("Joe");

    if( count==1) {
        cout<<"I can update safely I have one matching record" << std::endl;
        // bind parameter this way does not work with all wt version
        dbo::ptr<User> joe = session->find<User>().where("name = ?").bind("Joe");

        if(joe) {
            cout <<"we found joe updating karma now"<< std::endl;
            joe.modify()->setKarma(joe->getKarma() +1);
            cout<< "flush to database" <<std::endl;
            session->flush();
            cout <<" done i am closing transaction"<< std::endl;

            transaction.commit();
        }
    }
}
/*! \fn void deleteUserJoeOnly(dbo::Session* session)
* \brief deleting a  user from database note wt doesn't cascade delete
*
* \param session a handle to a dbo database
*example creating the session object \n
*cout<<" Create database connection \n";\n
*dbo::backend::Sqlite3 sqlite3("blog.db");\n
*dbo::Session session;\n
* \return nothing
*/
void deleteUserJoeOnly(dbo::Session* session)
{
    cout<<" start transaction to update values of user joe  "<< std::endl;

    dbo::Transaction transaction(*session);
    cout<<" looking for  user Joe in database may throw exception if not found " <<std::endl;
    int count = session->query<int>("select count(1) from user").where("name = ?").bind("Joe");

    if( count==1) {
        cout<<"I can delete safely I have one matching record" << std::endl;
        // bind parameter this way does not work with all wt version
        //to delete children too you need to define Post with
        //     dbo::belongsTo(a, author, "author", Wt::Dbo::OnDeleteCascade | Wt::Dbo::OnUpdateCascade);
        dbo::ptr<User> joe = session->find<User>().where("name = ?").bind("Joe");

        if(joe) {

            cout <<"we found joe will delete user now"<< std::endl;
            joe.remove();
            cout<< "flush to database" <<std::endl;
            session->flush();
            cout <<" done i am closing transaction"<< std::endl;

            transaction.commit();
        }
    }
}
