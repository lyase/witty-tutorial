/** \file  UserManagement.h
*A
header file defining user class
this class holds 
integration for FB user 
*\n
*then run with
*\code  ./test \endcode
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
#ifndef USERMANAGEMENT_HPP
 *\author:  ,Matthew Sherborne <msherborne@gmail.com>
  */
#ifndef USERMANAGEMENT_HPP
#define USERMANAGEMENT_HPP

#include <memory>

class UserManagement {
private:
    class Impl;
    std::unique_ptr<Impl> _impl;
public:
    UserManagement();
    ~UserManagement();
    static UserManagement& instance();
};

#endif // USERMANAGEMENT_HPP
