#include "AdminWindow.hpp"

#include <sstream>

/** Gets historical stock inforation from yahoo:
  * API Specifcation: http://code.google.com/p/yahoo-finance-managed/wiki/csvHistQuotesDownload
  */
void AdminWindow::addSeries(int col, MarkerType marker=NoMarker,SeriesType lineSeries=LineSeries)
{
     WDataSeries series(col, lineSeries);
     series.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
     series.setMarker(marker);
     chart->addSeries(series);
};
AdminWindow::AdminWindow(Wt::WContainerWidget* parent): Wt::WContainerWidget(parent), yahoo(new YahooStockHistory(this))
{
     _debugOutput = new Wt::WText(this);
     addWidget(new Wt::WBreak());
     std::stringstream buildinfo;
     buildinfo << "Compiled on " << __DATE__ << " at " << __TIME__ << "<br/>"
               << "Doc Root: " << Wt::WApplication::instance()->docRoot();
     log("DEBUG") << buildinfo.str();
     _debugOutput->setText(buildinfo.str());
     addWidget(new Wt::WBreak());
     new Wt::WAnchor(Wt::WLink("/generetedStatic/doc/html/index.html"), "show docs", this);
// copy below here from line 165 to 250 of file charExample.C but you need function readCsvFile to compile for now in cvsUtils.c in comments
     new WText(WString::tr("scatter plot"), this);
// for file privider
     //WAbstractItemModel *model = readCsvFile(WApplication::appRoot() + "timeseries.csv", this);
// for yahoo data provider
     model = yahoo->provideModelObject(this);
     if (!model)
          return;
// Show a view that allows editing of the model.

     WContainerWidget *w = new WContainerWidget(this);
     WTableView *table = new WTableView(w);
     table->setMargin(10, Top | Bottom);
     table->setMargin(WLength::Auto, Left | Right);
     table->setModel(model);
     table->setSortingEnabled(false); // Does not make much sense for time series
     table->setColumnResizeEnabled(true);
     table->setSelectionMode(NoSelection);
     table->setAlternatingRowColors(true);
     table->setColumnAlignment(0, AlignCenter);
     table->setHeaderAlignment(0, AlignCenter);
     table->setRowHeight(22);
// Editing does not really work without Ajax, it would require an
// additional button somewhere to confirm the edited value.
     if (WApplication::instance()->environment().ajax()) {
          table->resize(800, 20 + 5*22);
          table->setEditTriggers(WAbstractItemView::SingleClicked);
     } else {
          table->resize(800, 20 + 5*22 + 25);
          table->setEditTriggers(WAbstractItemView::NoEditTrigger);
     }
     table->setColumnWidth(0, 80);
     for (int i = 0; i < model->columnCount(); ++i)
          table->setColumnWidth(i, 90);
     /*
        * Create the scatter plot.
        */
     WCartesianChart *chart = new WCartesianChart(this);
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
     WDataSeries s(1, LineSeries);
     WDataSeries smoins1(2, LineSeries);
     WDataSeries smoins2(3, LineSeries);
     WDataSeries smoins3(4, LineSeries);

     s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
     chart->addSeries(smoins1);
     chart->addSeries(smoins2);
     chart->addSeries(smoins3);
     chart->addSeries(s);
     chart->resize(800, 400); // WPaintedWidget must be given explicit size

     chart->setMargin(10, Top | Bottom);            // add margin vertically
     chart->setMargin(WLength::Auto, Left | Right); // center horizontally

     //    new ChartConfig(chart, this); unknown purpose
//     Yahoo query apparatus
     Wt::WContainerWidget*  row = new Wt::WContainerWidget(parent);
     row->setStyleClass("row-fluid");
     Wt::WLabel* lbl = new Wt::WLabel("yahoo query:", row);
     Wt::WLineEdit* txt = new Wt::WLineEdit("GOOG", row);
     lbl->setBuddy(txt);
     goBtn = new Wt::WPushButton("Go!", row);

     // you may comment 2 following lines to compile with gmap widget
     // and line 65 of AdminWindow.hp
     map_ = new Wt::WGoogleMap(Wt::WGoogleMap::Version3);
     mapexample = new GoogleMapExample(this);
     new WText(WString::tr("you should see map above this"), this);
     /*      // Need start and end dates this creates internal wt error
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
     */

     modelUpdater = new Wt::WTimer(this);
     modelUpdater->setInterval(100);
     auto updatePrices = [this]() {
          yahoo->updateModelWithFakePrices(model);
     };
     modelUpdater->timeout().connect(std::bind(updatePrices));
     goBtn->clicked().connect(modelUpdater, &Wt::WTimer::start);
};
