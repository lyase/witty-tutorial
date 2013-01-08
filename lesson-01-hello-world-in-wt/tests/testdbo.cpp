/** \file  testdbo.cpp
*source file developper test using DBConfig struct
*\n
 *\version  0.1
 *\date 01/07/12 10:
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:
 *
 * =====================================================================================
 *//*
 * Copyright (C) 2009 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include <boost/test/unit_test.hpp>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WDate>
#include <Wt/WDateTime>
#include <Wt/WTime>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/ptr_tuple>
#include <Wt/Dbo/QueryModel>
#include <Wt/WLogger>
#include <Wt/Dbo/Query>
#include <boost/tuple/tuple.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>
#include "../DBConfigEntry.hpp"
#define BOOST_TEST_MODULE test_dbo

#include <boost/test/unit_test.hpp>

struct DBOFixture {
    Wt::WLogger logger;
    Wt::Dbo::backend::Sqlite3 conn;
    Wt::Dbo::Session session;
    DBOFixture() : conn(":memory:") {
        logger.configure("* -debug");
        logger.addField("datetime", false);
        logger.addField("type", false);
        logger.addField("message", true);
        conn.setProperty("show-queries", "true");
        session.setConnection(conn);
        DBConfig::mapTables(session);
        DBConfig::install(session);
    }
    ~DBOFixture() {
        DBConfig::uninstall(session);
    }
};


BOOST_FIXTURE_TEST_SUITE( dbo_test, DBOFixture )

BOOST_AUTO_TEST_CASE( dbo_test1 )
{
    //Create starting logger
    logger.entry("info") << Wt::WLogger::timestamp << Wt::WLogger::sep
                         << '[' << "notice" << ']' << Wt::WLogger::sep << "Starting up server!";


    // Check that the default parameters were loaded
    bool dosPuzzle = DBConfig::getConfigOption<bool>(session, "DosPuzzle");
    BOOST_CHECK_EQUAL(dosPuzzle, true);

    // Todo: check more config options



}

BOOST_AUTO_TEST_SUITE_END()
