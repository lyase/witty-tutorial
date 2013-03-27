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

#include <boost/lexical_cast.hpp>

#include <math.h>
#include <fstream>
#include <iterator>
#include <sstream>
#include <limits>



#ifndef BUILD_INFO
#define BUILD_INFO "No build info"
#endif

/** Gets historical stock inforation from yahoo:
  * API Specifcation: http://code.google.com/p/yahoo-finance-managed/wiki/csvHistQuotesDownload
  */
class AdminWindow::YahooStockHistory : public Wt::WObject {
public:
    enum TradingPeriod {daily='d', monthly='m', weekly='w'};
    typedef Wt::Signal<boost::system::error_code, Wt::Http::Message> GotCSVSignal;
private:
    Wt::Http::Client* http = new Wt::Http::Client(this);
    GotCSVSignal& query(const string& query) {
        std::string url = "http://ichart.yahoo.com/table.csv?";
        url += query;
        auto app = Wt::WApplication::instance();
        app->log("info") << "Sending query: " << url << "\n";
        if (http->get(url)) {
            return http->done();
        }
        throw std::runtime_error("Couldn't connect to http");
    }
    std::string urlEncode(const std::string& input) {
        std::stringstream result;
        auto in = input.begin();
        auto end = input.end();
        while (in != end) {
            if (((*in <= 'Z') && (*in >= 'A')) ||
                ((*in <= 'a') && (*in >= 'z')) ||
                ((*in <= '9') && (*in >= '0')) ||
                ((*in == '-') || (*in == '+'))) {
                result << *in++;
            } else if (*in == ' ') {
                result << '+';
                ++in;
            } else {
                result << '%' << std::hex << (int)(*in++) << ';';
            }
        }
        return result.str();
    }
public:
    YahooStockHistory(Wt::WObject* parent=nullptr) : Wt::WObject(parent) {}
    GotCSVSignal& query(const string& id, const Wt::WDate& start, const Wt::WDate& end, TradingPeriod interval) {
        std::stringstream url;
        url << "s=" << urlEncode(id)
            << "&a=" << (start.month() - 1)
            << "&b=" << start.day()
            << "&c=" << start.year()
            << "&d=" << (end.month() - 1)
            << "&e=" << end.day()
            << "&f=" << end.year()
            << "&g=" << interval
            << "&ignore=.csv";
        return query(url.str());
    }
};


AdminWindow::AdminWindow(Wt::WContainerWidget* parent)
    : Wt::WContainerWidget(parent),
      yahoo(new YahooStockHistory(this))
{
    parent->setStyleClass("container-fluid");
    _debugOutput = new Wt::WText(parent);
    _debugOutput->setText(Wt::WString("debug info: ") +  BUILD_INFO + " Docroot: " + Wt::WApplication::instance()->docRoot());
    cout << std::endl << std::endl <<  " Docroot: " << Wt::WApplication::instance()->docRoot()<<"::"<<std::endl;
    new Wt::WAnchor(Wt::WLink("/generetedStatic/doc/html/index.html"), "show docs", parent);
    // copy below here from line 165 to 250 of file charExample.C but you need function readCsvFile to compile for now in cvsUtils.c in comments
    new Wt::WText(Wt::WString::tr("scatter plot"), parent);

    /*
     * Create the scatter plot.
     */
    chart = new Wt::Chart::WCartesianChart(parent);
    //chart->setPreferredMethod(WPaintedWidget::PngImage);
    //chart->setBackground(gray);
    chart->setLegendEnabled(true); // enable the legend

    chart->setType(Wt::Chart::ScatterPlot);            // set type to ScatterPlot
    chart->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateScale); // set scale of X axis to DateScale

    // Provide space for the X and Y axis and title.
    chart->setPlotAreaPadding(80, Wt::Left);
    chart->setPlotAreaPadding(40, Wt::Top | Wt::Bottom);

    chart->resize(800, 400); // WPaintedWidget must be given explicit size

    chart->setMargin(10, Wt::Top | Wt::Bottom);            // add margin vertically
    chart->setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right); // center horizontally

    // Add what all the widgets we have so far to the vertical box layout

    // Yahoo query apparatus
    auto row = new Wt::WContainerWidget(parent);
    row->setStyleClass("row-fluid");

    auto lbl = new Wt::WLabel("yahoo query:", row);
    auto txt = new Wt::WLineEdit("GOOG", row);
    lbl->setBuddy(txt);
    goBtn = new Wt::WPushButton("Go!", row);

    // Need start and end dates
    row = new Wt::WContainerWidget(parent);
    row->setStyleClass("row-fluid");

    auto today = Wt::WDate::currentDate();
    lbl = new Wt::WLabel("From:", row);
    auto start = new Wt::WDatePicker(row);
    start->setDate(today.addMonths(-1));
    lbl->setBuddy(start->lineEdit());

    lbl = new Wt::WLabel("From:", row);
    auto end = new Wt::WDatePicker(row);
    lbl->setBuddy(end->lineEdit());
    end->setDate(today);

    goBtn->clicked().connect(goBtn, &Wt::WPushButton::disable);
    goBtn->clicked().connect([=](const Wt::WMouseEvent&) {
        auto& gotit = yahoo->query(
            txt->text().toUTF8(), start->date(), end->date(), YahooStockHistory::daily);
        gotit.connect(this, &AdminWindow::gotCSV);
    });
//    new ChartConfig(chart, this); unknown purpose
}

void AdminWindow::gotCSV(boost::system::error_code, Wt::Http::Message msg) {
    std::stringstream csv(msg.body());
    std::cout << csv.str() << "\n";
    /*
      Sample data that we are parsing;

    Date,Open,High,Low,Close,Volume,Adj Close
    2013-03-25,812.41,819.23,806.82,809.64,1712000,809.64
    2013-03-22,814.74,815.24,809.64,810.31,1488200,810.31
    2013-03-21,811.29,816.92,809.85,811.26,1466800,811.26
    */
    auto log = [](char* level=nullptr){return Wt::log(level == nullptr ? "debug" : level);};
    log() << "Reading Chart data";
    auto model = new  Wt::WStandardItemModel(this);
    // Read in the header
    std::string linein;
    std::getline(csv, linein);
    log() << "Read header row: " << linein;
    {   // Set Headers
        std::stringstream headers(linein);
        std::string header;
        int i=0;
        while (std::getline(headers, header, ',')) {
            model->insertColumn(i);
            log() << "Setting header: " << header;
            model->setHeaderData(i++, Wt::Horizontal, boost::any(header));
            std::getline(headers, header, ',');
        }
    }
    namespace Cht = Wt::Chart;
    chart->axis(Cht::XAxis).autoLimits();
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::lowest();
    while (true) {
        std::vector<Wt::WStandardItem*> row(7);
        auto pItem = row.begin();
        if (!std::getline(csv, linein))
            break;
        log() << "Reading line:" << linein;
        std::stringstream line(linein);
        // Parse into bits
        // Get the date
        std::string part;
        std::getline(line, part, ',');
        log() << "Reading date: " << part;
        auto date = Wt::WDate::fromString(part, "yyyy-mm-dd");
        *pItem = new Wt::WStandardItem();
        (*pItem)->setData(boost::any(date));
        // Opening Price, High, Low, Close, Adjusted Close
        size_t todo = 5;
        while (todo--) {
            // Don't read in the volume for now
            if (todo == 2)
                continue;
            std::getline(line, part, ','); // Open
            log() << "Reading value: " << part;
            *++pItem = new Wt::WStandardItem();
            double val = boost::lexical_cast<double>(part);
            if (val < min) min = val;
            if (val > max) max = val;
            (*pItem)->setData(boost::any(val));
        }
        model->appendRow(row);
    }

    // Now show the data in the chart
    auto& y = chart->axis(Cht::YAxis);
    y.setMinimum(min);
    y.setMaximum(max);
    chart->setModel(model);
    chart->setXSeriesColumn(0);
    chart->addSeries(1);
    chart->addSeries(2);
    chart->addSeries(3);
    chart->addSeries(4);
    /*
    auto addSeries = [=](int col, Cht::MarkerType marker=Cht::NoMarker) {
        Cht::WDataSeries series(col);
        series.setMarker(marker);
        chart->addSeries(series);
    };
    addSeries(1, Cht::CircleMarker); // Open
    chart->addSeries(Cht::WDataSeries(2, Cht::LineSeries));  // High
    chart->addSeries(Cht::WDataSeries(3, Cht::LineSeries));  // Low
    addSeries(4, Cht::SquareMarker); // Close
    chart->addSeries(Cht::WDataSeries(3, Cht::CurveSeries));  // Adjusted Close
    */
    log("notice") << "Chart Updated";
    goBtn->enable();
};
