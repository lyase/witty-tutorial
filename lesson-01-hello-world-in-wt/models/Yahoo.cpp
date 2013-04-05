#include"Yahoo.hpp"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>


std::string YahooStockHistory::urlEncode(const std::string& input)
{
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
};

YahooStockHistory::YahooStockHistory(Wt::WObject* parent): Wt::WObject(parent) { };

YahooStockHistory::GotCSVSignal& YahooStockHistory::query(const std::string& query)
{
     std::string url = "http://ichart.yahoo.com/table.csv?";
     url += query;
     Wt::WApplication* app = Wt::WApplication::instance();
     app->log("info") << "Sending query: " << url << "\n";
     if (http->get(url)) {
          return http->done();
     }
     throw std::runtime_error("Couldn't connect to http");
};
YahooStockHistory::GotCSVSignal& YahooStockHistory::query(const std::string& id, const Wt::WDate& start, const Wt::WDate& end, TradingPeriod interval)
{
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
};
/*this will convert data internal form to  Wt::WStandardItemModel ( table format for wt widget YahooStockHistory
 **/
Wt::WAbstractItemModel * YahooStockHistory::provideModelObject(  Wt::WContainerWidget *parent)
{
     Wt::WStandardItemModel *model = new Wt::WStandardItemModel(366, 2, parent);
     model->setHeaderData(0, std::string("Date"));
     model->setHeaderData(1, std::string("Price"));
     /* i will generate fake data in model as exemple 365 rows, 6 col*/
     /*
      * set  the first column as dates every day from (1988,6,14) to (1987,6,14);
      */
     std::cout<<"the model \n"<<model<<std::endl;
     Wt:: WDate d(1988,6,14);

     Wt::WDateTime now = Wt::WDateTime::currentDateTime();

     std::default_random_engine generator(now.toTime_t());
     std::uniform_real_distribution<double> hundred(1,100);
     double price = hundred(generator);

     for( int i = 0; i<365; i++) {
          //   Wt::WDate d =  Wt::WDate::currentDate();
          // this is very long could be refactored as we need only one new row
          model->setData(i, 0, boost::any(d));
          std::uniform_real_distribution<double> five(-5,5);
          price += five(generator);
          model->setData(i, 1, boost::any(price));
          d = d.addDays(1);
     }// end row

     std::cout<<"created model \n"<<model<<std::endl;
     return model;
};
