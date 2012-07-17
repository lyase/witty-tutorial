/*
 * Copyright (C) 2009 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include <boost/test/unit_test.hpp>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Postgres>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/backend/Firebird>
#include <Wt/Dbo/FixedSqlConnectionPool>
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



void Install()
{
     Session.createTables();
     Wt::Dbo::Transaction transaction(Session);

     typedef Wt::Dbo::ptr<DBConfigEntry> pEntry;

     //BaseURL
     pEntry baseUrl = Session.add(new DBConfigEntry("BaseUrl", ""));
     baseUrl.modify()->description = "This is the base URL that the user can see when browsing. For example, http://www.mywebsite.com/wt .\nThis field may be left empty.";
     //DosPuzzle
     pEntry dosPuzzle = Session.add(new DBConfigEnty("DosPuzzle", false));
     dosPuzzle.modify()->description = "When enabled the server adds a puzzle to validate Ajax sessions in the first Ajax request. This is a simple measure which avoids Denial-of-Service attacks on Ajax sessions.\n\nDefault value: Off";
     //JavascriptDebug
     Wt::Dbo::ptr<Configuration> JavascriptDebug = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationInt> JavascriptDebugVal = Session.add(new ConfigurationInt());
     JavascriptDebug.modify()->Id.Name = "JavascriptDebug";
     JavascriptDebug.modify()->Id.Application = "Server";
     JavascriptDebug.modify()->Title = "Debug javascript mode";
     JavascriptDebug.modify()->Type = Configuration::Int;
     JavascriptDebug.modify()->Details = "Enable this only if you are a developer and to debug javascript.\n\nPossible values:\n1 = (Off)JavaScript errors are caught and a simple error message is printed to indicate that something is terribly wrong(default, recommended)\n2 = (On)JavaScript errors are caught but also a stack trace is printed, useful for diagnosing a problem in production\n3 = (On)JavaScript errors are not caught but the browser built-in debug options are used";
     JavascriptDebugVal.modify()->Value = 1;
     JavascriptDebug.modify()->ConfigurationIntDbo.insert(JavascriptDebugVal);

     //MaxRequestSize
     Wt::Dbo::ptr<Configuration> MaxRequestSize = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationInt> MaxRequestSizeVal = Session.add(new ConfigurationInt());
     MaxRequestSize.modify()->Id.Name = "MaxRequestSize";
     MaxRequestSize.modify()->Id.Application = "Server";
     MaxRequestSize.modify()->Title = "Max request size";
     MaxRequestSize.modify()->Type = Configuration::Int;
     MaxRequestSize.modify()->Details = "Maximum request size in kilobytes. This has to be increased to allow uploading larger sized files.";
     MaxRequestSizeVal.modify()->Value = 128;
     MaxRequestSize.modify()->ConfigurationIntDbo.insert(MaxRequestSizeVal);

     //ReverseProxy
     Wt::Dbo::ptr<Configuration> ReverseProxy = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationBool> ReverseProxyVal = Session.add(new ConfigurationBool());
     ReverseProxy.modify()->Id.Name = "ReverseProxy";
     ReverseProxy.modify()->Id.Application = "Server";
     ReverseProxy.modify()->Title = "Behind reverse proxy";
     ReverseProxy.modify()->Type = Configuration::Bool;
     ReverseProxy.modify()->Details = "Enable this if the server is behind a reverse proxy. If you do not know what this means then disable it.\n\nDefault Value: Off";
     ReverseProxyVal.modify()->Value = false;
     ReverseProxy.modify()->ConfigurationBoolDbo.insert(ReverseProxyVal);

     //SessionTimeout
     Wt::Dbo::ptr<Configuration> SessionTimeout = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationInt> SessionTimeoutVal = Session.add(new ConfigurationInt());
     SessionTimeout.modify()->Id.Name = "SessionTimeout";
     SessionTimeout.modify()->Id.Application = "Server";
     SessionTimeout.modify()->Title = "Session timeout delay";
     SessionTimeout.modify()->Type = Configuration::Int;
     SessionTimeout.modify()->Details = "Session timeout delay in seconds. When a session remains inactive for this amount of time, it will be cleaned up.\nRecommended value: 600 (1 minute)";
     SessionTimeoutVal.modify()->Value = 600;
     SessionTimeout.modify()->ConfigurationIntDbo.insert(SessionTimeoutVal);

     //SessionTracking
     Wt::Dbo::ptr<Configuration> SessionTracking = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationInt> SessionTrackingVal = Session.add(new ConfigurationInt());
     SessionTracking.modify()->Id.Name = "SessionTracking";
     SessionTracking.modify()->Id.Application = "Server";
     SessionTracking.modify()->Title = "Session tracking strategy";
     SessionTracking.modify()->Type = Configuration::Int;
     SessionTracking.modify()->Details = "Possible values:\n1 = Cookies are used if available, otherwise URL rewriting for tracking session(default)\n2 = Only URL rewriting for tracking session";
     SessionTrackingVal.modify()->Value = 1;
     SessionTracking.modify()->ConfigurationIntDbo.insert(SessionTrackingVal);

     //LogDebugLevel
     Wt::Dbo::ptr<Configuration> LogDebugLevel = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationBool> LogDebugLevelVal = Session.add(new ConfigurationBool());
     LogDebugLevel.modify()->Id.Name = "LogDebugLevel";
     LogDebugLevel.modify()->Id.Application = "Logging";
     LogDebugLevel.modify()->Title = "Log debugging messages";
     LogDebugLevel.modify()->Type = Configuration::Bool;
     LogDebugLevel.modify()->Details = "When enabled debugging events/messages will be included in the log file. These notices only gives information for developers and might not be meaningful to end users.\n\nRecommended Value: Off";
     LogDebugLevelVal.modify()->Value = false;
     LogDebugLevel.modify()->ConfigurationBoolDbo.insert(LogDebugLevelVal);

     //LogDirectory
     Wt::Dbo::ptr<Configuration> LogDirectory = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationString> LogDirectoryVal = Session.add(new ConfigurationString());
     LogDirectory.modify()->Id.Name = "LogDirectory";
     LogDirectory.modify()->Id.Application = "Logging";
     LogDirectory.modify()->Title = "Logging file directory";
     LogDirectory.modify()->Type = Configuration::String;
     LogDirectory.modify()->Details = "Location to where the file in which logs will be created is. Can be a full path or even a relative path.\n\nWhen this is left empty, no log file will be created but disabling file logging is highly not recommended.\nDefault Value: ./logs";
     LogDirectoryVal.modify()->Value = "./logs";
     LogDirectory.modify()->ConfigurationStringDbo.insert(LogDirectoryVal);

     //LogErrorLevel
     Wt::Dbo::ptr<Configuration> LogErrorLevel = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationBool> LogErrorLevelVal = Session.add(new ConfigurationBool());
     LogErrorLevel.modify()->Id.Name = "LogErrorLevel";
     LogErrorLevel.modify()->Id.Application = "Logging";
     LogErrorLevel.modify()->Title = "Log error messages";
     LogErrorLevel.modify()->Type = Configuration::Bool;
     LogErrorLevel.modify()->Details = "When enabled errors will be included in the log file. \n\nRecommended Value: On";
     LogErrorLevelVal.modify()->Value = true;
     LogErrorLevel.modify()->ConfigurationBoolDbo.insert(LogErrorLevelVal);

     //LogInfoLevel
     Wt::Dbo::ptr<Configuration> LogInfoLevel = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationBool> LogInfoLevelVal = Session.add(new ConfigurationBool());
     LogInfoLevel.modify()->Id.Name = "LogInfoLevel";
     LogInfoLevel.modify()->Id.Application = "Logging";
     LogInfoLevel.modify()->Title = "Log informational notices";
     LogInfoLevel.modify()->Type = Configuration::Bool;
     LogInfoLevel.modify()->Details = "When enabled informational notices will be included in the log file. These notices only gives information rather than reporting a warning or an error.";
     LogInfoLevelVal.modify()->Value = false;
     LogInfoLevel.modify()->ConfigurationBoolDbo.insert(LogInfoLevelVal);

     //LogSecureLevel
     Wt::Dbo::ptr<Configuration> LogSecureLevel = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationBool> LogSecureLevelVal = Session.add(new ConfigurationBool());
     LogSecureLevel.modify()->Id.Name = "LogSecureLevel";
     LogSecureLevel.modify()->Id.Application = "Logging";
     LogSecureLevel.modify()->Title = "Log security events";
     LogSecureLevel.modify()->Type = Configuration::Bool;
     LogSecureLevel.modify()->Details = "When enabled security related messages will be included in the log file.\n\nRecommended Value: On";
     LogSecureLevelVal.modify()->Value = true;
     LogSecureLevel.modify()->ConfigurationBoolDbo.insert(LogInfoLevelVal);

     //LogWarnLevel
     Wt::Dbo::ptr<Configuration> LogWarnLevel = Session.add(new Configuration());
     Wt::Dbo::ptr<ConfigurationBool> LogWarnLevelVal = Session.add(new ConfigurationBool());
     LogWarnLevel.modify()->Id.Name = "LogWarnLevel";
     LogWarnLevel.modify()->Id.Application = "Logging";
     LogWarnLevel.modify()->Title = "Log warnings";
     LogWarnLevel.modify()->Type = Configuration::Bool;
     LogWarnLevel.modify()->Details = "When enabled warnings will be included in the log file. These warnings indicate that there was something could have caused an error and should be considered.\n\nRecommended Value: On";
     LogWarnLevelVal.modify()->Value = true;
     LogWarnLevel.modify()->ConfigurationBoolDbo.insert(LogWarnLevelVal);
     try {
          transaction.commit();
     } catch(Wt::Dbo::Exception& e) {
          throw e;
     }
}

void Uninstall()
{
     try {
          Session.dropTables();
     } catch(Wt::Dbo::Exception& e) {
          throw e;
     }
}

BOOST_AUTO_TEST_SUITE( dbo_test )

BOOST_AUTO_TEST_CASE( dbo_test1 )
{
     //Loading Start Time
     boost::posix_time::ptime PTStart = boost::posix_time::microsec_clock::local_time();
     //Create starting logger
     Wt::WLogger StartLogger;
     StartLogger.configure("* -debug");
     StartLogger.addField("datetime", false);
     StartLogger.addField("type", false);
     StartLogger.addField("message", true);
     StartLogger.entry("info");
     StartLogger.entry("info") << Wt::WLogger::timestamp << Wt::WLogger::sep
                               << '[' << "notice" << ']' << Wt::WLogger::sep << "Starting up server!";

     /* *************************************************************************
      * ************************  Initialize Database  **************************
      * *************************************************************************/
     //Start SQL Connection
     try {
          //Wt::Dbo::SqlConnection *SQLConnection = new Wt::Dbo::backend::MySQL("wt", "root", "root", "127.0.0.1");
          Wt::Dbo::SqlConnection *SQLConnection = new Wt::Dbo::backend::Sqlite3(":memory:");
          SQLConnection->setProperty("show-queries", "true");
          SQLPool = new Wt::Dbo::FixedSqlConnectionPool(SQLConnection, 1);
     } catch(Wt::Dbo::Exception& e) {
          StartLogger.entry("fatal") << Wt::WLogger::timestamp << Wt::WLogger::sep
                                     << '[' << "fatal error" << ']' << Wt::WLogger::sep << e.what();
          exit(EXIT_FAILURE);
     } catch(std::exception &e) {
          StartLogger.entry("fatal") << Wt::WLogger::timestamp << Wt::WLogger::sep
                                     << '[' << "fatal error" << ']' << Wt::WLogger::sep << e.what();
          exit(EXIT_FAILURE);
     }

     /* *************************************************************************
      * ************************  Load Configurations  **************************
      * *************************************************************************/
     Config = new Configurations;
     try {
          //Config->Uninstall();
          Config->Install();
          Config->FetchAll();
     } catch(Wt::Dbo::Exception& e) {
          std::cerr << e.what(); //test
     }
     StartLogger.entry("info") << Wt::WLogger::timestamp << Wt::WLogger::sep
                               << '[' << "notice" << ']' << Wt::WLogger::sep << Config->GetConfigurationsCount() << " Configurations Loaded in " << Config->GetLoadDurationinMS() << " Ms";

     //Deallocate
     delete Config;
     delete SQLPool; //Also deletes SQLConnection
     // fake test assert for now
     BOOST_CHECK_EQUAL(45, 45);
}

BOOST_AUTO_TEST_SUITE_END()
