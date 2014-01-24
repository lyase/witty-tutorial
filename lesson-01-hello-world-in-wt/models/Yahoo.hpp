#ifndef YAHOO_H
#define YAHOO_H
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <hpdf.h>
#include <iostream>
#include <iterator>
#include <limits>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WDataSeries>
#include <Wt/Chart/WPieChart>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Dbo>
#include <Wt/Http/Client>
#include <Wt/Render/WPdfRenderer>
#include <Wt/WAbstractItemModel>
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WBorderLayout>
#include <Wt/WContainerWidget>
#include <Wt/WDate>
#include <Wt/WDatePicker>
#include <Wt/WEnvironment>
#include <Wt/WFitLayout>
#include <Wt/WItemDelegate>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WLink>
#include <Wt/WPushButton>
#include <Wt/WSignal>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WString>
#include <Wt/WTableView>
#include <Wt/WText>
class YahooStockHistory : public Wt::WObject {
public:
     enum TradingPeriod {daily='d', monthly='m', weekly='w'};
     typedef Wt::Signal<boost::system::error_code, Wt::Http::Message> GotCSVSignal;
     YahooStockHistory(Wt::WObject* parent=NULL);
     GotCSVSignal& query(const std::string& query);
     GotCSVSignal& query(const std::string& id, const Wt::WDate& start, const Wt::WDate& end, TradingPeriod interval) ;
     Wt::WAbstractItemModel * provideModelObject(  Wt::WContainerWidget* parent );
private:
     Wt::Http::Client* http;
     std::string urlEncode(const std::string& input) ;
};

#endif // YAHOO_H
