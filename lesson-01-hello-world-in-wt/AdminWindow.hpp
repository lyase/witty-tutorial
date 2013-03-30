#ifndef ADMINWINDOW_HPP
#define ADMINWINDOW_HPP
/// This window sows admin monitoring option get to documentation build log and test results

#include <Wt/WContainerWidget>
#include <Wt/Chart/WCartesianChart>
#include <boost/system/error_code.hpp>
#include "HelloApp.hpp"
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WApplication>
#include "CsvUtil.h"
#include <Wt/WDate>
#include <Wt/WDatePicker>
#include <Wt/WEnvironment>
#include <Wt/WItemDelegate>
#include <Wt/WStandardItemModel>

#include <Wt/WStandardItem>
#include <Wt/WTableView>

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>
#include <Wt/Http/Client>
#include <Wt/WSignal>
#include <Wt/WBorderLayout>
#include <Wt/WFitLayout>

#include <Wt/WStandardItem>
#include <Wt/WTableView>
#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>
#include <Wt/Chart/WDataSeries>
#include <boost/lexical_cast.hpp>

#include <math.h>
#include <fstream>
#include <iterator>
#include <sstream>
#include <limits>
using namespace Wt;
using namespace Wt::Chart;
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
     WAbstractItemModel *model;
    void handlePathChanged(const std::string& newPath);
    void gotCSV(boost::system::error_code, Wt::Http::Message msg);
    Wt::Chart::WCartesianChart* chart;
public:
    AdminWindow(Wt::WContainerWidget* parent=0);
};

#endif // ASKWINDOW_HPP
