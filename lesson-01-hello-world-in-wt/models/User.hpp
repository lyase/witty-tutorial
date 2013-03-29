/** \file  User.h
*header file defining user class
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
#ifndef USER_H
#define USER_H
#include <Wt/Dbo/Dbo>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/Types>
#include <string>
#include <Wt/WDate>
#include <Wt/WString>
#include <Wt/Dbo/collection>
#include <Wt/Dbo/WtSqlTraits>
#include <string>
#include <ctype.h>
#include <Wt/Dbo/Impl>
#include <Wt/WDate>
#include <Wt/WString>
#include <Wt/Auth/User>
#include <Wt/Dbo/WtSqlTraits>

#include "Post.hpp"

namespace dbo = Wt::Dbo;
using namespace std ;
/** An enum type. defining the status of the User
*
*/

enum Role {
    Visitor ,/**< enum the User is no identified just a visitor value 0 */
    Admin , /**< the user is log in and is Admin value 1 */
    Alien  /**< the user is nothing  value 2 */
};

/*! A User   class
* \details This class is used to demonstrate a number of section commands.
* \author John Doe
* \version 4.1a
* \date 1990-2011
* \pre First initialize the system.
* \bug  should be bug free was check with valgrind  in prg testUser_Class_dbo.cpp
* \warning Improper use can crash your application.
*
*/
/*! \brief  this class defines a User object  of the application
*this class now has  Posts as children
*/
class User;

typedef Wt::Auth::Dbo::AuthInfo<User> AuthInfo;

typedef		dbo::collection< dbo::ptr<User> > Users;

class User : public Wt::Auth::User {
private:
    string m_name; /*!< a string with name of User */
    string m_password;/*!< variable is password in  clear  */
    Role        m_role; /*!< represents the identified status of the user admin.... */
    int         m_karma; /*!< an integer value */
public:
    Posts posts;
    /*! \fn template<class Action> void persist(Action& a)
    * \brief A required function for wt::dbo
    * it is the field <->var member mapping table
    * for dbo internal use
    * \param a a Action .
    */
    template<class Action> void persist(Action& a) {
        dbo::field(a, m_name,     "name");
        dbo::field(a, m_password, "password");
        dbo::field(a, m_role,     "role");
        dbo::field(a, m_karma,    "karma");
        dbo::hasMany(a, posts,      dbo::ManyToOne, "author");


    }
    User();
    ~User();
    /*! \fn void setName(string str)
    * \brief A setter for private member name.
    * \param str a string .
    * \return a void if all ok.
    */
    void setName(string);
    /*! \fn void setPassword(string str)
    * \brief A setter for private member password.
    * \param str a string with password.
    * \return a void with status.
    */
    void setPassword(string);
    /*! \fn  void setRole(Role Role)
    * \brief A setter for private member Role.
    * \param Role a Role .
    * \return a void if all ok.
    */
    void setRole(Role);
    /*! \fn  void  render2pdf()
    * \brief render to hello.pdf all information about User */
    void render2pdf();

    /*! \fn  void setKarma(int)
    * \brief A setter for private member Karma.
    * \return a void  if all ok.
    */
    void setKarma(int);
    /*! \fn  string getName() const;
    * \brief A getter for private member Name.
    * \return the name as string if all ok.
    * */
    string getName() const;
    /*! \fn  string getPassword() const;
    * \brief A getter for private member Password.
    * \return the password as string if all ok.
    */
    string getPassword() const;
    /*! \fn   Role getRole() const
    * \brief A getter for private member Name.
    * \return the role as role (int) if all ok. should throw exception otherwise
    */
    Role getRole() const;
    /*! \fn       int getKarma() const;
    * \brief A getter for private member karma.
    * \return the role as role (int) if all ok.should throw exception otherwise
    */
    int getKarma() const;

};
/*!\var Users
 * *\brief collection of user
 * derived from  dbo::collection
 * usualy returned after as results of dbo query
 **/


#endif
