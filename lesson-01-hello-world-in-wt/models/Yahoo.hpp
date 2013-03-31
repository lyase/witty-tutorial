#ifndef YAHOO_H
#define YAHOO_H
#include <Wt/WContainerWidget>
#include <Wt/Chart/WCartesianChart>
#include <boost/system/error_code.hpp>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WApplication>

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
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <Wt/WEnvironment>
#include <Wt/WItemDelegate>
#include <Wt/WStandardItemModel>
#include <Wt/WText>
#include <iostream>
#include <Wt/WStandardItem>
#include <Wt/WContainerWidget>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <Wt/WAbstractItemModel>
#include <Wt/WString>

#include <Wt/WBorderLayout>
#include <Wt/WFitLayout>

#include <Wt/WStandardItem>
#include <Wt/WTableView>

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>

#include <Wt/WAbstractItemModel>
#include <Wt/WString>
#include <iostream>
#include <fstream>
#include <math.h>
#include <fstream>
#include <iterator>
#include <sstream>
#include <limits>
#include <Wt/Dbo/Dbo>

#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Render/WPdfRenderer>
#include <hpdf.h>
class YahooStockHistory : public Wt::WObject {
public:
    enum TradingPeriod {daily='d', monthly='m', weekly='w'};
    typedef Wt::Signal<boost::system::error_code, Wt::Http::Message> GotCSVSignal;
    YahooStockHistory(Wt::WObject* parent);
    GotCSVSignal& query(const std::string& query);
    GotCSVSignal& query(const std::string& id, const Wt::WDate& start, const Wt::WDate& end, TradingPeriod interval) ;
    Wt::WAbstractItemModel * provideModelObject(  Wt::WContainerWidget* parent );
private:
    Wt::Http::Client* http = new Wt::Http::Client(this);
    std::string urlEncode(const std::string& input) ;
};

#endif // YAHOO_H
