#ifndef POST_HPP
#define POST_HPP

#include <Wt/WDate>
#include <Wt/WString>
#include <Wt/Dbo/Dbo>

/*! A Post   class
* \details This class is  a document contents created by a user of app
* this class has dbo support example of Many-to-One relations with user.
* \author Lyase damasked from wt/dbo/tutorial.html
* \version 4.1a
* \date 1990-2012
* \pre First initialize the system.
* \bug .
*
*/

class User;

namespace dbo = Wt::Dbo;

class Post : public Wt::Dbo::Dbo<Post> {
public:
    enum State {
        Unpublished = 0,
        Published = 1
    };

    dbo::ptr<User> author;
    State          state;

    Wt::WDateTime  date;
    Wt::WString    title;
    Wt::WString    briefSrc;
    Wt::WString    briefHtml;
    Wt::WString    bodySrc;
    Wt::WString    bodyHtml;
    std::string permaLink() const {return date.toString("yyyy/MM/dd/'" +  '\'').toUTF8();}
    template<class Action>
    void persist(Action& a) {
        dbo::field(a, state,     "state");
        dbo::field(a, date,      "date");
        dbo::field(a, title,     "title");
        dbo::field(a, briefSrc,  "brief_src");
        dbo::field(a, briefHtml, "brief_html");
        dbo::field(a, bodySrc,   "body_src");
        dbo::field(a, bodyHtml,  "body_html");
        dbo::belongsTo(a, author, "author", Wt::Dbo::OnDeleteCascade | Wt::Dbo::OnUpdateCascade);
    }
};

typedef		dbo::collection< dbo::ptr<Post> > Posts;

#endif // POST_HPP
