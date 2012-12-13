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

namespace test_helpers {

template <class Widget>
void click(Widget* widget) {
    Wt::WMouseEvent click;
    widget->clicked().emit(click);
}

template <>
void click<Wt::WAnchor>(Wt::WAnchor* widget) {
    const Wt::WLink& link = widget->link();
    switch (link.type()) {
    case Wt::WLink::Url:  // A static URL.
    case Wt::WLink::Resource:   // A dynamic resource.
    case Wt::WLink::InternalPath: // An internal path.
        Wt::WApplication* app = Wt::WApplication::instance();
        app->setInternalPath(link.internalPath().toUTF8(), true);
    }
}

}
