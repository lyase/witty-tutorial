/*! \file test_user_is_not_mike.cpp
* =====================================================================================
* \brief this  is a simple test app to be used by cmake ctest this app will return 0 if ok
  return -1 if error
*
* \author Matthew Sherborne (), msherborne@gmail.com
* \version 0.1
* \date 6 septembre 2007
* \bug       None known to date
* \warning   Improper use can crash your application
* \copyright GNU Public License.
* =====================================================================================*/
#include "../models/User.h"
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    User u;
    if (u.getName() == "John") {
        std::cerr << "name is already john precondition is not met I can not run this test the current name is  " << u.getName() << std::endl;
        return -1;
    } else {
        u.setName("John");
        std::string name = u.getName();
        if (name == "John") {
            return 0;
        } else {
            std::cerr << "Expected set name to set the name to 'John' but it set it to " << name << std::endl;
            return -1; // Failed test
        }
    }
}
