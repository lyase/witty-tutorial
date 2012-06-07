/** \file  IWebPageFactory.h
*    Description:  defines a Factory interface for WwebPages Factory of a Wt web application
* you need to have a Concrete implementation of thhis class for your webSite to run  
*\n
*\version  1.0
 *\date 31/05/12 10:06:50
  *       Revision:  none
   *       Compiler:  gcc
    *
     *\author:  lyase.d, lyase.d@gmail.com
      *        Company:  
       *
        * =====================================================================================
         */

#ifndef IWEBPAGEFACTORY_H
#define IWEBPAGEFACTORY_H
// need the interface helper
#include <Wt/WContainerWidget>
#include"CppInterfaces_helpers.h"// helper to define interfaces
// IWebPageFactory.h
// this will create the interface 
// so in  //class Foo :  implements IWebPageFactory will add the IWebPageFactory interface to class
class testing;
DeclareInterface(IWebPageFactory)
        virtual void createWebPage(const std::string, Wt::WContainerWidget* ) = 0;

        //{  };
//you  can implement here if not pure virtual remove =0 at declaration of function
// if pure virtual you can not instanciate this object
//it is an interface no object should be created from this definition
//but you can create a pointer and instanciate the class 
/*
example below create a pointer on interface with pure virtual
ithen create objects implementing interface
set pointer to objects
use functions of the interface 
Command* mcmdswitch;
TurnOn a(mlight);
TurnOff b(mlight);
if(i%2==0)
{
mcmdswitch=&a;
else{
mcmdswitch=&b;
}
mcmdswitch->execute();
*mcmdswitch.execute();// dereferencing pointer not working ??
delete mcmdswitch;
*/     


EndInterface
#endif

