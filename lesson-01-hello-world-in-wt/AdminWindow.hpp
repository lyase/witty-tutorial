#ifndef ADMINWINDOW_HPP
#define ADMINWINDOW_HPP
/// This window sows admin monitoring option get to documentation build log and test results

#include <Wt/WContainerWidget>

// Forward Declarations
namespace Wt {
class WLineEdit;
class WText;
class WLabel;
class WButton;
class WLink;
}

class AdminWindow : public Wt::WContainerWidget {
private:
    class YahooStockHistory;
    Wt::WText* _debugOutput;
    YahooStockHistory* yahoo;
    void handlePathChanged(const std::string& newPath);
    void gotCSV(const std::string& newPath);
public:
    AdminWindow(Wt::WContainerWidget* parent=0);
};

#endif // ASKWINDOW_HPP
