/** \file  User.cpp
*source file defining user class
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
 */
// $Log$
  
///  Single line comment for dOxygen.
  
/**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)
   
   The function arguments listed with "param" will be compared
   to the declaration and verified.
 
   @param[in]     _inArg1 Description of first function argument.
   @param[out]    _outArg2 Description of second function argument.
   @param[in,out] _inoutArg3 Description of third function argument.
   @return Description of returned value.
 */
  

#include <Wt/Dbo/Dbo>
#include "User.h"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
// compile with g++ listing.cpp -o test -l wtdbosqlite3

namespace dbo = Wt::Dbo;
using namespace std ;
User::User()
{
cout<<"creating new user\n";
    m_name="aUserName";
    m_password="aUserpassword";
    setRole(Visitor);
    m_karma=1;
};
User::~User()
{
    cout <<"destroying user\n ";
}
void User::setName(string myName)
{
    m_name=myName;
    return ; 
}
void User::setPassword(string myPass)
{
    m_password=myPass;
    return ;
}
void User::setRole(Role myRole)
{
    m_role=myRole;
    return ;
}
void User::setKarma(int myKarma)
{
    m_karma=myKarma;
    return ;
}

string User::getName() const
{
    return m_name; 
}
string User::getPassword() const
{
   
    return m_password;
}
Role User::getRole() const
{
    return m_role;
}
int User::getKarma() const
{
    return m_karma;
}
