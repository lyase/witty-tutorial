/** \file  HelloFactory.hpp
*implementation of the HelloFactory factory a Factory that manages a web site saying hello
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
#ifndef HELLOFACTORY_H_
#define HELLOFACTORY_H_
#include"IWebPageFactory.h"
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "AdminWindow.hpp"
#include <iostream>

class HelloFactory :  implements WebPageFactory
{

// Construction & Destruction
public:
  
    HelloFactory()
    {
    std::cout<< " creating  helloFactory a concrete  WebPageFactory";
    }
      
      ~HelloFactory()
      { 
        std::cout<<"destroying a  helloFactory\n";
      }
// the  implementationof the function required by interface definition could be better in a cpp file
    virtual void createWebPage(const std::string newPath, Wt::WContainerWidget* aroot )
      { 
// you can add more pages here such as the admin page
        if (newPath == "/ask")
        new AskWindow(aroot);
        else if (newPath == "/say")
        new SayWindow(aroot);
        else
        new MainWindow(aroot);
}

};
#endif
