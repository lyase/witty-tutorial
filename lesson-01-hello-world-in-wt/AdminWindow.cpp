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
#include <math.h>
#include <fstream>
#include <iterator>
#include <sstream>


#include <Wt/Http/Client>
#include <Wt/WSignal>

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

    Wt::WAbstractItemModel *model = readCsvFile(
      Wt::WApplication::appRoot() + "timeseries.csv", this);

    if (!model)
      return;

    /*
     * Parses the first column as dates, to be able to use a date scale
     */
    for (int i = 0; i < model->rowCount(); ++i) {
      Wt::WString s = Wt::asString(model->data(i, 0));
      auto d = Wt::WDate::fromString(s, "dd/MM/yy");
      model->setData(i, 0, d);
    }

    // Show a view that allows editing of the model.
    Wt::WTableView* table = new Wt::WTableView(parent);

    table->setMargin(10, Wt::Top | Wt::Bottom);
    table->setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right);

    table->setModel(model);
    table->setSortingEnabled(false); // Does not make much sense for time series
    table->setColumnResizeEnabled(true);
    table->setSelectionMode(Wt::NoSelection);
    table->setAlternatingRowColors(true);
    table->setColumnAlignment(0, Wt::AlignCenter);
    table->setHeaderAlignment(0, Wt::AlignCenter);
    table->setRowHeight(22);

    // Editing does not really work without Ajax, it would require an
    // additional button somewhere to confirm the edited value.
    if (Wt::WApplication::instance()->environment().ajax()) {
      table->resize(800, 20 + 5*22);
      table->setEditTriggers(Wt::WAbstractItemView::SingleClicked);
    } else {
      table->resize(800, 20 + 5*22 + 25);
      table->setEditTriggers(Wt::WAbstractItemView::NoEditTrigger);
    }

    /*
    WItemDelegate *delegate = new WItemDelegate(this);
    delegate->setTextFormat("%.1f");
    table->setItemDelegate(delegate);
    table->setItemDelegateForColumn(0, new WItemDelegate(this));
    */

    table->setColumnWidth(0, 80);
    for (int i = 1; i < model->columnCount(); ++i)
      table->setColumnWidth(i, 90);

    /*
     * Create the scatter plot.
     */
    auto chart = new Wt::Chart::WCartesianChart(parent);
    //chart->setPreferredMethod(WPaintedWidget::PngImage);
    //chart->setBackground(gray);
    chart->setModel(model);        // set the model
    chart->setXSeriesColumn(0);    // set the column that holds the X data
    chart->setLegendEnabled(true); // enable the legend

    chart->setType(Wt::Chart::ScatterPlot);            // set type to ScatterPlot
    chart->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateScale); // set scale of X axis to DateScale

    // Provide space for the X and Y axis and title.
    chart->setPlotAreaPadding(80, Wt::Left);
    chart->setPlotAreaPadding(40, Wt::Top | Wt::Bottom);

    /*
     * Add first two columns as line series
     */
    for (int i = 1; i < 3; ++i) {
      Wt::Chart::WDataSeries s(i, Wt::Chart::LineSeries);
      s.setShadow(Wt::WShadow(3, 3, Wt::WColor(0, 0, 0, 127), 3));
      chart->addSeries(s);
    }

    chart->resize(800, 400); // WPaintedWidget must be given explicit size

    chart->setMargin(10, Wt::Top | Wt::Bottom);            // add margin vertically
    chart->setMargin(Wt::WLength::Auto, Wt::Left | Wt::Right); // center horizontally

    // Add what all the widgets we have so far to the vertical box layout

    // Yahoo query aparatus
    auto row = new Wt::WContainerWidget(parent);
    row->setStyleClass("row-fluid");

    auto lbl = new Wt::WLabel("yahoo query:", row);
    auto txt = new Wt::WLineEdit("GOOG", row);
    lbl->setBuddy(txt);
    auto btn = new Wt::WPushButton("Go!", row);

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

    btn->clicked().connect([=](const Wt::WMouseEvent&) {
        yahoo->query(txt->text().toUTF8(), start->date(),
                     end->date(), YahooStockHistory::daily).connect(this, &AdminWindow::gotCSV);
    });
//    new ChartConfig(chart, this); unknown purpose
}

void AdminWindow::gotCSV(boost::system::error_code, Wt::Http::Message msg) {
    std::stringstream csv(msg.body());
    std::cout << csv.str() << "\n";
};
