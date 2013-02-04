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
#include <Wt/WApplication>
#include <Wt/WDate>
#include <Wt/WEnvironment>
#include <Wt/WItemDelegate>
#include <Wt/WStandardItemModel>
#include <Wt/WText>

#include <Wt/WBorderLayout>
#include <Wt/WFitLayout>

#include <Wt/WStandardItem>
#include <Wt/WTableView>

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>
#include <math.h>
#include <fstream>

//#include "ChartsExample.h"
//#include "ChartConfig.h"
#include "CsvUtil.h"

#include <Wt/WApplication>
#include <Wt/WDate>
#include <Wt/WEnvironment>
#include <Wt/WItemDelegate>
#include <Wt/WStandardItemModel>
#include <Wt/WText>

#include <Wt/WBorderLayout>
#include <Wt/WFitLayout>

#include <Wt/WStandardItem>
#include <Wt/WTableView>

#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>

using namespace Wt;
using namespace Wt::Chart;
#ifndef BUILD_INFO
#define BUILD_INFO "No build info"
#endif

AdminWindow::AdminWindow(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent)
{
    _debugOutput = new Wt::WText(this);
    addWidget(new Wt::WBreak());
    std::string buildinfo;
    buildinfo = BUILD_INFO;
    _debugOutput->setText(Wt::WString("debug info: " + buildinfo + " Docroot: " + Wt::WApplication::instance()->docRoot()));
    cout <<std::endl<< std::endl <<  " Docroot: " << Wt::WApplication::instance()->docRoot()<<"::"<<std::endl;
    //_debugOutput->setText("debug info "+buildinfo);
    addWidget(new Wt::WBreak());
    new Wt::WAnchor(Wt::WLink("/generetedStatic/doc/html/index.html"), "show docs", this);
    // copy below here from line 165 to 250 of file charExample.C but you need function readCsvFile to compile for now in cvsUtils.c in comments
    new WText(WString::tr("scatter plot"), this);

    WAbstractItemModel *model = readCsvFile(
      WApplication::appRoot() + "timeseries.csv", this);

    if (!model)
      return;

    /*
     * Parses the first column as dates, to be able to use a date scale
     */
    for (int i = 0; i < model->rowCount(); ++i) {
      WString s = asString(model->data(i, 0));
      WDate d = WDate::fromString(s, "dd/MM/yy");
      model->setData(i, 0, d);
    }

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
    for (int i = 1; i < 3; ++i) {
      WDataSeries s(i, LineSeries);
      s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
      chart->addSeries(s);
    }

    chart->resize(800, 400); // WPaintedWidget must be given explicit size

    chart->setMargin(10, Top | Bottom);            // add margin vertically
    chart->setMargin(WLength::Auto, Left | Right); // center horizontally

//    new ChartConfig(chart, this); unknown purpose
  }
