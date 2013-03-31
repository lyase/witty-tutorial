/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <stdlib.h>
#include <boost/tokenizer.hpp>
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

#include <Wt/WAbstractItemModel>
#include <Wt/WString>
#include <iostream>
#include <fstream>
using namespace std;
using namespace Wt;
using namespace Wt::Chart;
#include "CsvUtil.h"
// example using this function can be seen in fonction WAbstractItemModel *readCsvFile(const std::string &fname,WContainerWidget *parent)
// in file:///home/ubsafder/temp/dojo/witty-tutorial/wt/examples/charts/ChartsExample.C

void readFromCsv(std::istream& f, Wt::WAbstractItemModel *model,
         int numRows, bool firstLineIsHeaders)
{
  int csvRow = 0;

  while (f) {
    std::string line;
    getline(f, line);

    if (f) {
      typedef boost::tokenizer<boost::escaped_list_separator<char> >
    CsvTokenizer;
      CsvTokenizer tok(line);

      int col = 0;
      for (CsvTokenizer::iterator i = tok.begin();
       i != tok.end(); ++i, ++col) {

    if (col >= model->columnCount())
      model->insertColumns(model->columnCount(),
                   col + 1 - model->columnCount());

    if (firstLineIsHeaders && csvRow == 0)
      model->setHeaderData(col, boost::any(Wt::WString::fromUTF8(*i)));
    else {
      int dataRow = firstLineIsHeaders ? csvRow - 1 : csvRow;

      if (numRows != -1 && dataRow >= numRows)
        return;

      if (dataRow >= model->rowCount())
        model->insertRows(model->rowCount(),
                  dataRow + 1 - model->rowCount());

      boost::any data;
      std::string s = *i;

      char *endptr;

      if (s.empty())
        data = boost::any();
      else {
        double d = strtod(s.c_str(), &endptr);
        if (*endptr == 0)
          data = boost::any(d);
        else
          data = boost::any(Wt::WString::fromUTF8(s));
      }

      model->setData(dataRow, col, data);
    }
      }
    }

    ++csvRow;
  }
}

/*
 * Reads a CSV file as an (editable) standard item model.
 */
WAbstractItemModel *readCsvFile(const std::string &fname,
                WContainerWidget *parent)
{
  WStandardItemModel *model = new WStandardItemModel(0, 0, parent);
  std::ifstream f(fname.c_str());

  if (f) {
    readFromCsv(f, model);

    for (int row = 0; row < model->rowCount(); ++row)
  for (int col = 0; col < model->columnCount(); ++col) {
    model->item(row, col)->setFlags(ItemIsSelectable | ItemIsEditable);

    /*
      Example of tool tips (disabled here because they are not updated
      when editing data)
     */

    /*
    WString toolTip = asString(model->headerData(col)) + ": "
      + asString(model->item(row, col)->data(DisplayRole), "%.f");
    model->item(row, col)->setToolTip(toolTip);
     */
  }
    /*
     * Parses the first column as dates, to be able to use a date scale
     */
    for (int i = 0; i < model->rowCount(); ++i) {
      WString s = asString(model->data(i, 0));
      Wt::WDate d = Wt::WDate::fromString(s, "dd/MM/yy");
      model->setData(i, 0, d);
    }
    return model;
  } else {
    WString error(WString::tr("error-missing-data"));
    error.arg(fname, UTF8);
    new WText(error, parent);
    return 0;
  }
}
