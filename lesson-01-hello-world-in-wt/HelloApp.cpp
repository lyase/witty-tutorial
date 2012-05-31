/** \file  HelloApp.cpp
*    Description:  code for the  web app a wt Hello world in c++
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  Matthew Sherborne (), msherborne@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "HelloApp.hpp"
#include "AskWindow.hpp"
#include "SayWindow.hpp"
#include "MainWindow.hpp"
#include "IWebPageFactory.h"

HelloApp::HelloApp(const Wt::WEnvironment& env, WebPageFactory* theFactory) : Wt::WApplication(env) 
{
setTitle("Hello world");
user = new User();
mFactory=theFactory;
internalPathChanged().connect(this, &HelloApp::handlePathChanged);
    // The user could enter our app on any url, so let's show the correct thing
handlePathChanged(internalPath());
}
/**
* \fn void void HelloApp::handlePathChanged(const std::string& newPath)
* \brief this function will be called each time the user changes webpage
* this function should create the view ( web page) by instantiating the apropriate Window object a  Wt::WContainerWidget
* \param newPath contains path of the page been asked
*
 * \return nothing
*/
void HelloApp::handlePathChanged(const std::string& newPath) 
{
root()->clear();
mFactory->createWebPage(newPath);
    /* manual  way of doing things now implemented in the Factory
    if (newPath == "/ask")
        new AskWindow(root());
    else if (newPath == "/say")
        new SayWindow(root());
    else
        new MainWindow(root());
        */
}
