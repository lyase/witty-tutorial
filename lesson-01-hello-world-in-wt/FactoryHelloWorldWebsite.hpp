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
#ifndef HELLOFACTORY_H_
#define HELLOFACTORY_H_
#include <Wt/WObject>
#include <Wt/WApplication>
#include"IWebPageFactory.h"
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "AdminWindow.hpp"
#include "MainWindow.hpp"
#include <iostream>
/*! \class HelloFactory
*      \brief this class is a WebPage Factory\n
*    it will instantiante web pages when asked for the web app \n
* to build a hello web site
*   two pages   url:/ask =>a web page asking user name \n
*               url:/say=>a web page welcoming user by name*/
enum WebPage_codeName {say,ask,admin,landing};

class FactoryHelloWorldWebsite :  public Wt::WObject, public IWebPageFactory {
     // Construction & Destruction
public:
     FactoryHelloWorldWebsite(Wt::WObject* parent) : Wt::WObject(parent) {
          std::cout<< " creating  helloFactory a concrete  WebPageFactory\n";
     }
     ~FactoryHelloWorldWebsite() {
          std::cout<<"destroying a helloFactory\n";
     }
     WebPage_codeName hashit (std::string const& inString) {
          if (inString == "/ask") return ask;
          if (inString == "/say") return say;
          if (inString == "/admin") return admin;
          /* default page will be the landing the MainWindow*/
          return landing;
     }

     // the  implementation of the function required by interface definition could be better in a cpp file
     virtual void createWebPage(const std::string newPath, Wt::WContainerWidget* aroot ) {
          // we are using an enum you can  add more pages here but  best implementation with a Map
          // see https://github.com/matiu2/witty-plus/blob/master/wittyPlus/base/URLs.hpp

          Wt::WApplication::instance()->log("info") << "Create web page called: " << newPath;
          switch (hashit(newPath)) {
          case ask:
               new AskWindow(aroot);
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
};
#endif
