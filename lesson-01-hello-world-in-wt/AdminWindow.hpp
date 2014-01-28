#ifndef ADMINWINDOW_HPP
#define ADMINWINDOW_HPP
/// This window sows admin monitoring option get to documentation build log and test results

#include"GoogleMapExample.hpp"
#include <Wt/WContainerWidget>
#include <Wt/Chart/WCartesianChart>
#include <boost/system/error_code.hpp>
#include "HelloApp.hpp"
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WGoogleMap>
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
#include "models/Yahoo.hpp"
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
     Wt::WText* _debugOutput;
// GoogleMapExample *map     Wt::WGoogleMap* map_ ;
     GoogleMapExample *mapexample ;
     Wt::WPushButton* goBtn;
     YahooStockHistory* yahoo;
     WAbstractItemModel *model;
     Wt::Chart::WCartesianChart* chart;
     void handlePathChanged(const std::string& newPath);
     void gotCSV(boost::system::error_code, Wt::Http::Message msg);
     void addSeries (int col, MarkerType marker, SeriesType LineSeries);
public:
     // AdminWindow(Wt::WContainerWidget* parent=0);
     AdminWindow(Wt::WContainerWidget* parent=0);
};

#endif // ASKWINDOW_HPP
