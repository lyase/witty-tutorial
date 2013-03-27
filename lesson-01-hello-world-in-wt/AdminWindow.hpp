#ifndef ADMINWINDOW_HPP
#define ADMINWINDOW_HPP
/// This window sows admin monitoring option get to documentation build log and test results

#include <Wt/WContainerWidget>
#include <Wt/Chart/WCartesianChart>
#include <boost/system/error_code.hpp>

// Forward Declarations
namespace Wt {
class WLineEdit;
class WText;
class WLabel;
class WButton;
class WPushButton;
class WLink;
}

class AdminWindow : public Wt::WContainerWidget {
private:
    class YahooStockHistory;
    Wt::WText* _debugOutput;
    Wt::WPushButton* goBtn;
    YahooStockHistory* yahoo;
    void handlePathChanged(const std::string& newPath);
    void gotCSV(boost::system::error_code, Wt::Http::Message msg);
    Wt::Chart::WCartesianChart* chart;
public:
    AdminWindow(Wt::WContainerWidget* parent=0);
};

#endif // ASKWINDOW_HPP
