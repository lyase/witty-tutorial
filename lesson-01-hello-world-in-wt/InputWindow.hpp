#ifndef INPUTWINDOW_HPP
#define INPUTWINDOW_HPP
/// This window asks the user for their name, then stores it in the app object, then sends them to the "SayHi" page

#include <Wt/WContainerWidget>

// Forward Declarations
namespace Wt {
class WLineEdit;
class WText;
class WLabel;
class WButton;
class WLink;
}

class InputWindow : public Wt::WContainerWidget {
private:
     Wt::WLabel* _inputLabel;
     Wt::WLineEdit* _nameInput;
     Wt::WLineEdit* _pwordInput;
     Wt::WText* _nameOutput;
     Wt::WPushButton* _btnCreateUser;
     Wt::WPushButton* _btnToggleTheme;
     void sayHi();
     void handlePathChanged(const std::string& newPath);
public:
     InputWindow(Wt::WContainerWidget* parent=0);
};

#endif // ASKWINDOW_HPP
