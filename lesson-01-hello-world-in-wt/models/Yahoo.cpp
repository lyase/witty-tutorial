#include"Yahoo.hpp"
#include <cstdlib>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <math.h>       /* exp */
using boost::numeric_cast;
using boost::numeric::bad_numeric_cast;
std::string YahooStockHistory::urlEncode(const std::string& input)
{
     http = new Wt::Http::Client(this);
     std::stringstream result;
     std::string::const_iterator in = input.begin();
     std::string::const_iterator end = input.end();
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
     /* i will generate fake data in model as exemple 365 rows, 2 cols */
     /*
      * set  the first column 0 as dates every day from (1988,6,14) to (1989,6,13);
      *the second colum col=1 is prices a brownian motion log normal process r=5% sigma=10%( anualised)
      */
     std::cout<<"the model \n"<<model<<std::endl;
     Wt:: WDate d(1988,6,14);
     Wt::WDateTime now = Wt::WDateTime::currentDateTime();
     double r=exp(log(1.05)/365)-1.0;
     double sigma=0.10*sqrt(365); /* daily return  variance*/
     double price = 0;
     double ret=0; /* stock return in period*/
     for( int i = 0; i<365; i++) {
          model->setData(i, 0, boost::any(d));
          // std::uniform_real_distribution<double> five(-1,1);
          // random N(0,1) for brownian motion
          double wt = (((rand()%100)/100.0) -0.5)*2.0;
          ret= (1+r+sigma*wt/100);
          if (i!=0) {
               double oldPrice=boost::any_cast<double>((model->data((i-1),1)));
               // new price with brownian
               //
               price= oldPrice*ret ;
               //     price= ret; /* to  plot returns  values ~1 */
               //       price= wt;  /* to  plot random values N(0,1) */
               //price= i;
          } else {
               // it's the first date set price to unit to start brownian motion
               price=1;
          }
          model->setData(i, 1, boost::any(price));
          d = d.addDays(1);
     }// end row

     std::cout<<"created model \n"<<model<<std::endl;
     return model;
};
