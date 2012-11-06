#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <Wt/WContainerWidget>
#include <Wt/WString>
#include "User.h"
namespace Wt {
    class WLineEdit;
    class WText;
    class WLabel;
    class WButton;
    class WAnchor;
}

class MainWindow : public Wt::WContainerWidget {
private:
    Wt::WLabel* _inputLabel;
    Wt::WLineEdit* _nameInput;
    Wt::WText* _nameOutput;
    Wt::WPushButton* _btnHi;
    Wt::WString _lastNameEntered;
    Wt::WAnchor* _askLink;
    Wt::WAnchor* _adminLink;
/*! \fn MainWindow::sayHi()
* \brief a event handler behind the sayhi button on this page\n
*this function will update theuser model with input widget\n
*then update the ouput widget saying hello to user by name  \n
* \return nothing.
*/
    void sayHi();
public:
/*! \fn void MainWindow(Wt::WContainerWidget* parent)
* \brief a Constructor for the main page ( window) of the web app \n
put here all the widget needed on the page display
* \param  parent a Wt::WContainerWidget*.
* \return a new object if all ok.
*/
    MainWindow(Wt::WContainerWidget* parent=0);
    const Wt::WString& getLastName() { return _lastNameEntered; }
};

#endif // MAINWINDOW_HPP
