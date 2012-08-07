#include "AdminWindow.hpp"
#include "HelloApp.hpp"
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WApplication>

AdminWindow::AdminWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    _debugOutput = new Wt::WText(this);
    addWidget(new Wt::WBreak());
    std::string buildinfo;
    buildinfo="  ";
#define WRNG_PRIVATE_STR2(z) #z
#define WRNG_PRIVATE_STR1(x) WRNG_PRIVATE_STR2(x)
#define WRNG __FILE__ " Compiled at:("WRNG_PRIVATE_STR1(__TIME__)")line:("WRNG_PRIVATE_STR1(__LINE__)"): ------------ : "

//#define WRNG __FILE__ "("WRNG_PRIVATE_STR1(__LINE__)"): ------------ : "
    buildinfo+=WRNG ;
    _debugOutput->setText(Wt::WString("debug info: " + buildinfo + " Docroot: " + Wt::WApplication::instance()->docRoot()));
    cout <<std::endl<< std::endl <<  " Docroot: " << Wt::WApplication::instance()->docRoot()<<"::"<<std::endl;
    //_debugOutput->setText("debug info "+buildinfo);
    addWidget(new Wt::WBreak());
    new Wt::WAnchor(Wt::WLink("/generetedStatic/doc/html/index.html"), "show docs", this);
}


