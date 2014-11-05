/** \file  FactoryHelloWorldWebsite.hpp
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
#include <Wt/WObject>
#include "FactoryHelloWorldWebsite.hpp"
#include <Wt/WApplication>
#include"IWebPageFactory.h"
#include "InputWindow.hpp"
#include "SayWindow.hpp"
#include "AdminWindow.hpp"
#include "MainWindow.hpp"
#include <iostream>
FactoryHelloWorldWebsite::FactoryHelloWorldWebsite(Wt::WObject* parent) : Wt::WObject(parent)
{
     std::cout<< " creating  helloFactory a concrete  WebPageFactory\n";
}
FactoryHelloWorldWebsite::~FactoryHelloWorldWebsite()
{
     std::cout<<"destroying a helloFactory\n";
}
WebPage_codeName FactoryHelloWorldWebsite::hashit (std::string const& inString)
{
     if (inString == "/ask") return ask;
     if (inString == "/say") return say;
     if (inString == "/admin") return admin;
     /* default page will be the landing the MainWindow*/
     return landing;
}
void FactoryHelloWorldWebsite::createWebPage(const std::string newPath, Wt::WContainerWidget* aroot )
{
     // we are using an enum you can  add more pages here but  best implementation with a Map
     // see https://github.com/matiu2/witty-plus/blob/master/wittyPlus/base/URLs.hpp

     Wt::WApplication::instance()->log("info") << "Create web page called: " << newPath;
     switch (hashit(newPath)) {
     case ask:
          new InputWindow(aroot);
          break;
     case say:
          new SayWindow(aroot);
          break;
     case admin:
          new AdminWindow(aroot);
          break;
     case landing:
          new MainWindow(aroot);
          break;
     }
}
