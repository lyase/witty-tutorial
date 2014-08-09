#include "MainWindow.hpp"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WLink>
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WTheme>

MainWindow::MainWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
     _inputLabel = new Wt::WLabel("What is your name?", this);
     _nameInput = new Wt::WLineEdit(this);
     _nameInput->setFocus();
     _inputLabel->setBuddy(_nameInput);
     _btnHi = new Wt::WPushButton("Say Hi", this);
     _nameOutput = new Wt::WText(this);
     _btnHi->clicked().connect(this, &MainWindow::sayHi);
     _btnTogglePolishTheme = new Wt::WPushButton("Change to polished", this);
     _btnToggleDefaultTheme= new Wt::WPushButton("Change to default", this);
     _btnTogglePolishTheme->clicked().connect(this, &MainWindow::togglePolishedTheme);
     _btnToggleDefaultTheme->clicked().connect(this, &MainWindow::toggleDefaultTheme);

     new Wt::WAnchor(Wt::WLink("/docs.html"), "Show Docs", this);
}

void MainWindow::sayHi()
{
     Wt::WString name = _nameInput->valueText();
     if (name.empty())
          _nameOutput->setText("");
     else
          _nameOutput->setText("Hi there " + name);
}
void MainWindow::toggleDefaultTheme()
{
     Wt::WApplication* app = Wt::WApplication::instance(); // Get the Wt::WApplication intstance for our thread
     std::string oldTheme = "polished";
     oldTheme = app->theme()->name();
     std::string newTheme = "default";

     newTheme = oldTheme == "default" ? "polished" : "default";
     app->setCssTheme(newTheme); // Toggle the theme between 'default' and 'polished'
     _btnToggleDefaultTheme->hide();
     _btnTogglePolishTheme->setText("Change to  polished theme" );
     // Make the client reload the css
     app->doJavaScript(app->javaScriptClass() + ".updateStyles()");
     app->refresh();

}
void MainWindow::togglePolishedTheme()
{
     Wt::WApplication* app = Wt::WApplication::instance(); // Get the Wt::WApplication intstance for our thread

     std::string newTheme = "polished";
//     std::string newTheme = oldTheme == "default" ? "polished" : "default";
     app->setCssTheme(newTheme); // Toggle the theme between 'default' and 'polished'
     _btnToggleDefaultTheme->setText("Change to default");
     _btnTogglePolishTheme->hide();
     // Make the client reload the css
     app->doJavaScript(app->javaScriptClass() + ".updateStyles()");
     app->refresh();
}
