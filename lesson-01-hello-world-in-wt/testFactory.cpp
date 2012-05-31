/** \file  testFactory.cpp
*file testing HelloFactory is compiling with    g++ testFactory.cpp -o output
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

#include"HelloFactory.hpp"
int main(int argc, char** argv) {
WebPageFactory* mfactory;
HelloFactory a();
mfactory=&a;

mfacttory->createWebPage();
return 0;
}
