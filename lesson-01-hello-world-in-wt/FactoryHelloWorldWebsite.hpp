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
#include "InputWindow.hpp"
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
     FactoryHelloWorldWebsite(Wt::WObject* parent) ;
     ~FactoryHelloWorldWebsite();
     WebPage_codeName hashit (std::string const& inString) ;

     // the  implementation of the function required by interface definition could be better in a cpp file
     virtual void createWebPage(const std::string newPath, Wt::WContainerWidget* aroot );

};
#endif
