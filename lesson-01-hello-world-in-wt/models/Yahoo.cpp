#include"Yahoo.hpp"


std::string YahooStockHistory::urlEncode(const std::string& input) {
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

    YahooStockHistory::YahooStockHistory(Wt::WObject* parent=nullptr): Wt::WObject(parent) {int i;
                                                                                           i=0;
                                                                                           }
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
        }
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
    }


