// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef CSV_UTIL_H_
#define CSV_UTIL_H_

#include <iostream>
#include <Wt/WStandardItem>
#include <Wt/WContainerWidget>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <Wt/WAbstractItemModel>
#include <Wt/WString>
#include <Wt/WDate>
namespace Wt {
  class WAbstractItemModel;
}

/**
 * @addtogroup chartsexample
 */
/*@{*/

/*! \brief Utility function that reads a model from a CSV file.
 */
extern void readFromCsv(std::istream& f, Wt::WAbstractItemModel *model,int numRows = -1, bool firstLineIsHeaders = true);
Wt::WAbstractItemModel *readCsvFile(const std::string &, Wt::WContainerWidget *);
/*@}*/

#endif // CSV_UTIL_H_
