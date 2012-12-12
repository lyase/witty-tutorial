/** \file  User.cpp
*source file defining user class
*\n
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:
 *
 * =====================================================================================
 */
// $Log$

///  Single line comment for dOxygen.

/**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)

   The function arguments listed with "param" will be compared
   to the declaration and verified.

   @param[in]     _inArg1 Description of first function argument.
   @param[out]    _outArg2 Description of second function argument.
   @param[in,out] _inoutArg3 Description of third function argument.
   @return Description of returned value.
 */

#include<fstream>
#include <Wt/Dbo/Dbo>
#include "User.hpp"
#include <string>
#include <iostream>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Render/WPdfRenderer>
#include <Wt/WResource>
#include <hpdf.h>
// compile with g++ listing.cpp -o test -l wtdbosqlite3

namespace dbo = Wt::Dbo;
using namespace std ;
User::User() : Wt::Auth::User() {
    cout<<"creating new user\n";
    m_name="Joe";
    m_password="aUserpassword";
    setRole(Visitor);
    m_karma=1;
};
User::~User() {
    cout <<"destroying user\n ";
}
void User::setName(string myName) {
    m_name=myName;
    return ;
}
void User::setPassword(string myPass) {
    m_password=myPass;
    return ;
}
void User::setRole(Role myRole) {
    m_role=myRole;
    return ;
}
void User::setKarma(int myKarma) {
    m_karma=myKarma;
    return ;
}


void User::render2pdf() {
    cout<<"shouldbeImplemented this function should output all user's data to a pdf file or as a mime object  \n";
    // use a specialized  Wt::WResource Class to serve file see example in http://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WResource.html

//    Wt::WPdfImage a(100,100,"my test") ;
 Wt::WPdfImage pdfImage2(Wt::WLength(4, Wt::WLength::Centimeter),  Wt::WLength(3, Wt::WLength::Centimeter));
  { //draw on you pdf ressource
  //this is a fake render example just drawing a line
//   Wt::WPainter p(&pdfImage2);
     pdfImage2.drawLine(1,1,2,2);
  // best would be to pdfImage2.drawText( somewhere on the pdf draw "the user 's Name"
 //   chart->paint(p);
  }
  std::ofstream file("chart.pdf", std::ios::out | std::ios::binary);
  pdfImage2.write(file);

    return ;
}
string User::getName() const {
    return m_name;
}
string User::getPassword() const {

    return m_password;
}
Role User::getRole() const {
    return m_role;
}
int User::getKarma() const {
    return m_karma;
}
