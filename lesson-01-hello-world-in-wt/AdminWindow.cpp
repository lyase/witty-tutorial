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
  addWidget(new Wt::WBreak());
    new Wt::WAnchor(Wt::WLink("/docs.html"), "Show Docs", this);
}


