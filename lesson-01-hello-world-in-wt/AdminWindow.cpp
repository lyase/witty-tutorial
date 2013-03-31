#include "AdminWindow.hpp"

#ifndef BUILD_INFO
#define BUILD_INFO "No build info"
#endif

/** Gets historical stock inforation from yahoo:
  * API Specifcation: http://code.google.com/p/yahoo-finance-managed/wiki/csvHistQuotesDownload
  */

void AdminWindow::addSeries(int col, MarkerType marker=NoMarker,SeriesType LineSeries=LineSeries )
{
WDataSeries series(col , LineSeries);
series.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));

series.setMarker(marker);
chart->addSeries(series);
};

AdminWindow::AdminWindow(Wt::WContainerWidget* parent): Wt::WContainerWidget(parent), yahoo(new YahooStockHistory(this))
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
    chart->setModel(model);        // set the model
    chart->setXSeriesColumn(0);    // set the column that holds the X data
    chart->setLegendEnabled(true); // enable the legend

    chart->setType(ScatterPlot);            // set type to ScatterPlot
    chart->axis(XAxis).setScale(DateScale); // set scale of X axis to DateScale

    // Provide space for the X and Y axis and title.
    chart->setPlotAreaPadding(80, Left);
    chart->setPlotAreaPadding(40, Top | Bottom);

    /*
     * Add first two columns as line series
     */
    for (int i = 1; i < 3; ++i) {
      WDataSeries s(i, LineSeries);
      s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
      chart->addSeries(s);
    }

    chart->resize(800, 400); // WPaintedWidget must be given explicit size

    chart->setMargin(10, Top | Bottom);            // add margin vertically
    chart->setMargin(WLength::Auto, Left | Right); // center horizontally

//    new ChartConfig(chart, this); unknown purpose

    //chart->setPreferredMethod(WPaintedWidget::PngImage);
    //chart->setBackground(gray);
    chart->setLegendEnabled(true); // enable the legend

    chart->setType(Wt::Chart::ScatterPlot);            // set type to ScatterPlot
    chart->axis(Wt::Chart::XAxis).setScale(Wt::Chart::DateScale); // set scale of X axis to DateScale

         chart->setXSeriesColumn(0);    // set the column that holds the X data
        chart->setLegendEnabled(true); // enable the legend
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
        auto& gotit = yahoo->query(txt->text().toUTF8(), start->date(), end->date(), YahooStockHistory::daily);
        gotit.connect(this, &AdminWindow::gotCSV);
    }
);
//    new ChartConfig(chart, this); unknown purpose
}

void AdminWindow::gotCSV(boost::system::error_code, Wt::Http::Message msg) {
    std::stringstream csv(msg.body());
    std::cout <<"response from yahoo: "<< csv.str() << "\n";
    /*
      Sample data that we are parsing;

    Date,Open,High,Low,Close,Volume,Adj Close
    2013-03-25,812.41,819.23,806.82,809.64,1712000,809.64
    2013-03-22,814.74,815.24,809.64,810.31,1488200,810.31
    2013-03-21,811.29,816.92,809.85,811.26,1466800,811.26
    */
    auto log = [](char* level=nullptr){return Wt::log(level == nullptr ? "debug" : level);};
    log() << "Reading Chart data";

     model = new  Wt::WStandardItemModel(this);
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
    int csvRow = 0;
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
            // Don't read in the volume column 2 for now
            if (todo == 2)
                continue;
            std::getline(line, part, ','); // Open
            log() << "Read value: " << part;
            *++pItem = new Wt::WStandardItem();
            double val = boost::lexical_cast<double>(part);
            if (val < min) min = val;
            if (val > max) max = val;
            (*pItem)->setData(boost::any(val));
            model->insertRows(model->rowCount(),1);
            model->setData(csvRow, todo, val);
        }
      //  model->appendRow(row);

++csvRow;

    }
        chart->setModel(model);        // set the model
       chart->setXSeriesColumn(0);    // set the column that holds the X data
       chart->setLegendEnabled(true); // enable the legend
       chart->setType(ScatterPlot);            // set type to ScatterPlot
       chart->axis(XAxis).setScale(DateScale); // set scale of X axis to DateScale
       // Provide space for the X and Y axis and title.
       chart->setPlotAreaPadding(80, Left);
       chart->setPlotAreaPadding(40, Top | Bottom);
       // Now show the data in the chart
    auto& y = chart->axis(Cht::YAxis);
    y.setMinimum(min);
    y.setMaximum(max);
    chart->setModel(model);
    chart->setXSeriesColumn(1);
    chart->addSeries(1);
    chart->addSeries(2);
    chart->addSeries(3);
    chart->addSeries(4);

/*auto addSeries = [=](int col, Cht::MarkerType marker=Cht::NoMarker) {
WDataSeries series(col , LineSeries);
series.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));

series.setMarker(marker);
chart->addSeries(series);
};*/
addSeries(1, CircleMarker, LineSeries); // Open
addSeries(2, SquareMarker , LineSeries);  // High
addSeries(3, XCrossMarker,CurveSeries);  // Low
addSeries(4, SquareMarker,PointSeries); // Close
addSeries(3, TriangleMarker,CurveSeries);  // Adjusted Close

    log("notice") << "Chart Updated";
    goBtn->enable();
};
