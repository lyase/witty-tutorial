#include <Wt/WEvent>
#include <Wt/WApplication>
#include <Wt/WMenu>
#include <Wt/WMenuItem>
#include <Wt/WLink>
#include <Wt/WString>
#include <string>
#include <boost/test/test_tools.hpp>

#include <Wt/WAnchor>
#include <Wt/WApplication>
template <class Widget>
void click(Widget* widget) {
widget->click();
}
template <>
void click<Wt::WAnchor>(Wt::WAnchor* widget) {
const Wt::WLink& link = widget->link();
switch (link.type()) {
case Wt::WLink::Url:  // A static URL.
case Wt::Resource:   // A dynamic resource.
case Wt::InternalPath: // An internal path.
                                            {
Wt::WApplication* app = Wt::WApplication::instance();
app->setInternalPath(link.internalPath(), true);
}
}
}
