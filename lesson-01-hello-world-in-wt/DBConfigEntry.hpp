/** \file  BDConfig.hpp
*source file defining DBConfig struct
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
 */
#ifndef DBCONFIG_HPP
#define DBCONFIG_HPP

#include <string>
#include <Wt/Dbo/Dbo>

namespace DBConfig {
/*! A DBConfigEntry   class
* \details This class is a (key,variant) like object with dbo capabilities.
* in our application it will be used to store the  config parameters.
* usage see developper tests in \file  tests/testdbo.cpp bool dosPuzzle = DBConfig::getConfigOption<bool>(session, "DosPuzzle"); will fetch the value of DosPuzzle key in our database.
* see in this file void install(Wt::Dbo::Session& session) L154 how to create& store keys
        * \author Mattew
        * \version 0.1a
        * \date 1990-2012
        * \pre First initialize session obect with a database connection
        * \bug  none known
    * \warning all these object are stored in the same table there may not be any checks on unique key.
*
*/
struct DBConfigEntry {
    enum ValueType { vtString, vtDouble, vtInt };

    std::string key;
    std::string description;
    std::string asString;
    double asDouble;
    int asInt;
    ValueType valueType;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, key, "key");
        Wt::Dbo::field(a, description, "description");
        Wt::Dbo::field(a, valueType, "type");
        Wt::Dbo::field(a, asString, "asString");
        Wt::Dbo::field(a, asDouble, "asDouble");
        Wt::Dbo::field(a, asInt, "asInt");
    }

    // Constructors

    DBConfigEntry() {}

    DBConfigEntry(const std::string& key, const std::string& value, const std::string& description="") :
        key(key), description(description), asString(value), valueType(vtString) {}

    DBConfigEntry(const std::string& key, const char* value, const std::string& description="") :
        key(key), description(description), asString(value), valueType(vtString) {}

    DBConfigEntry(const std::string& key, double value, const std::string& description="") :
        key(key), description(description), asDouble(value), valueType(vtDouble) {}

    DBConfigEntry(const std::string& key, int value, const std::string& description=""):
        key(key), description(description), asInt(value), valueType(vtInt) {}

    DBConfigEntry(const std::string& key, bool value, const std::string& description=""):
        key(key), description(description), asInt(value ? 1 : 0), valueType(vtInt) {}

    // Cast operations

    operator std::string() const {
        assert(valueType == vtString);
        return asString;
    }

    operator double() const {
        assert(valueType == vtDouble);
        return asDouble;
    }

    operator int() const {
        assert(valueType == vtInt);
        return asInt;
    }

    operator bool() const {
        assert(valueType == vtInt);
        return asInt != 0;
    }

    // Setters

    DBConfigEntry& operator = (const std::string& newVal) {
        valueType = vtString;
        asString = newVal;
        return *this;
    }

    DBConfigEntry& operator = (double newVal) {
        valueType = vtDouble;
        asDouble = newVal;
        return *this;
    }


    DBConfigEntry& operator = (int newVal) {
        valueType = vtInt;
        asInt = newVal;
        return *this;
    }

    DBConfigEntry& operator = (bool newVal) {
        valueType = vtInt;
        asInt = newVal ? 1 : 0;
        return *this;
    }

    // Stream compatibility

    std::ostream& operator<< (std::ostream& o) {
        switch (valueType) {
        case vtString: {
            o << asString;
            break;
        }
        case vtDouble: {
            o << asDouble;
            break;
        }
        case vtInt: {
            o << asInt;
            break;
        }
        }
        return o;
    }

};

template<typename Type>
Type getConfigOption(Wt::Dbo::Session& session, const std::string& key, Type defaultVal=Type()) {
    Wt::Dbo::Transaction transaction(session);
    Wt::Dbo::ptr<DBConfigEntry> result = session.find<DBConfigEntry>().where("key = ?").bind(key);
    return result ? *result : defaultVal;
}

void mapTables(Wt::Dbo::Session& session) {
    session.mapClass<DBConfigEntry>("config_entries");
}

void install(Wt::Dbo::Session& session) {
    session.createTables();
    Wt::Dbo::Transaction transaction(session);

    typedef Wt::Dbo::ptr<DBConfigEntry> pEntry;

    //BaseURL
    pEntry baseUrl = session.add(new DBConfigEntry("BaseUrl", ""));
    baseUrl.modify()->description =
        "This is the base URL that the user can see when browsing. "
        "For example, http://www.mywebsite.com/wt .\nThis field may be left empty.";
    //DosPuzzle
    pEntry dosPuzzle = session.add(new DBConfigEntry("DosPuzzle", true));
    dosPuzzle.modify()->description = "When enabled the server adds a puzzle to validate Ajax sessions in the first Ajax request. This is a simple measure which avoids Denial-of-Service attacks on Ajax sessions.\n\nDefault value: Off";

    /*
    //JavascriptDebug
    Wt::Dbo::ptr<Configuration> JavascriptDebug = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationInt> JavascriptDebugVal = session.add(new ConfigurationInt());
    JavascriptDebug.modify()->Id.Name = "JavascriptDebug";
    JavascriptDebug.modify()->Id.Application = "Server";
    JavascriptDebug.modify()->Title = "Debug javascript mode";
    JavascriptDebug.modify()->Type = Configuration::Int;
    JavascriptDebug.modify()->Details = "Enable this only if you are a developer and to debug javascript.\n\nPossible values:\n1 = (Off)JavaScript errors are caught and a simple error message is printed to indicate that something is terribly wrong(default, recommended)\n2 = (On)JavaScript errors are caught but also a stack trace is printed, useful for diagnosing a problem in production\n3 = (On)JavaScript errors are not caught but the browser built-in debug options are used";
    JavascriptDebugVal.modify()->Value = 1;
    JavascriptDebug.modify()->ConfigurationIntDbo.insert(JavascriptDebugVal);

    //MaxRequestSize
    Wt::Dbo::ptr<Configuration> MaxRequestSize = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationInt> MaxRequestSizeVal = session.add(new ConfigurationInt());
    MaxRequestSize.modify()->Id.Name = "MaxRequestSize";
    MaxRequestSize.modify()->Id.Application = "Server";
    MaxRequestSize.modify()->Title = "Max request size";
    MaxRequestSize.modify()->Type = Configuration::Int;
    MaxRequestSize.modify()->Details = "Maximum request size in kilobytes. This has to be increased to allow uploading larger sized files.";
    MaxRequestSizeVal.modify()->Value = 128;
    MaxRequestSize.modify()->ConfigurationIntDbo.insert(MaxRequestSizeVal);

    //ReverseProxy
    Wt::Dbo::ptr<Configuration> ReverseProxy = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationBool> ReverseProxyVal = session.add(new ConfigurationBool());
    ReverseProxy.modify()->Id.Name = "ReverseProxy";
    ReverseProxy.modify()->Id.Application = "Server";
    ReverseProxy.modify()->Title = "Behind reverse proxy";
    ReverseProxy.modify()->Type = Configuration::Bool;
    ReverseProxy.modify()->Details = "Enable this if the server is behind a reverse proxy. If you do not know what this means then disable it.\n\nDefault Value: Off";
    ReverseProxyVal.modify()->Value = false;
    ReverseProxy.modify()->ConfigurationBoolDbo.insert(ReverseProxyVal);

    //SessionTimeout
    Wt::Dbo::ptr<Configuration> SessionTimeout = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationInt> SessionTimeoutVal = session.add(new ConfigurationInt());
    SessionTimeout.modify()->Id.Name = "SessionTimeout";
    SessionTimeout.modify()->Id.Application = "Server";
    SessionTimeout.modify()->Title = "session timeout delay";
    SessionTimeout.modify()->Type = Configuration::Int;
    SessionTimeout.modify()->Details = "session timeout delay in seconds. When a session remains inactive for this amount of time, it will be cleaned up.\nRecommended value: 600 (1 minute)";
    SessionTimeoutVal.modify()->Value = 600;
    SessionTimeout.modify()->ConfigurationIntDbo.insert(SessionTimeoutVal);

    //SessionTracking
    Wt::Dbo::ptr<Configuration> SessionTracking = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationInt> SessionTrackingVal = session.add(new ConfigurationInt());
    SessionTracking.modify()->Id.Name = "SessionTracking";
    SessionTracking.modify()->Id.Application = "Server";
    SessionTracking.modify()->Title = "session tracking strategy";
    SessionTracking.modify()->Type = Configuration::Int;
    SessionTracking.modify()->Details = "Possible values:\n1 = Cookies are used if available, otherwise URL rewriting for tracking session(default)\n2 = Only URL rewriting for tracking session";
    SessionTrackingVal.modify()->Value = 1;
    SessionTracking.modify()->ConfigurationIntDbo.insert(SessionTrackingVal);

    //LogDebugLevel
    Wt::Dbo::ptr<Configuration> LogDebugLevel = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationBool> LogDebugLevelVal = session.add(new ConfigurationBool());
    LogDebugLevel.modify()->Id.Name = "LogDebugLevel";
    LogDebugLevel.modify()->Id.Application = "Logging";
    LogDebugLevel.modify()->Title = "Log debugging messages";
    LogDebugLevel.modify()->Type = Configuration::Bool;
    LogDebugLevel.modify()->Details = "When enabled debugging events/messages will be included in the log file. These notices only gives information for developers and might not be meaningful to end users.\n\nRecommended Value: Off";
    LogDebugLevelVal.modify()->Value = false;
    LogDebugLevel.modify()->ConfigurationBoolDbo.insert(LogDebugLevelVal);

    //LogDirectory
    Wt::Dbo::ptr<Configuration> LogDirectory = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationString> LogDirectoryVal = session.add(new ConfigurationString());
    LogDirectory.modify()->Id.Name = "LogDirectory";
    LogDirectory.modify()->Id.Application = "Logging";
    LogDirectory.modify()->Title = "Logging file directory";
    LogDirectory.modify()->Type = Configuration::String;
    LogDirectory.modify()->Details = "Location to where the file in which logs will be created is. Can be a full path or even a relative path.\n\nWhen this is left empty, no log file will be created but disabling file logging is highly not recommended.\nDefault Value: ./logs";
    LogDirectoryVal.modify()->Value = "./logs";
    LogDirectory.modify()->ConfigurationStringDbo.insert(LogDirectoryVal);

    //LogErrorLevel
    Wt::Dbo::ptr<Configuration> LogErrorLevel = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationBool> LogErrorLevelVal = session.add(new ConfigurationBool());
    LogErrorLevel.modify()->Id.Name = "LogErrorLevel";
    LogErrorLevel.modify()->Id.Application = "Logging";
    LogErrorLevel.modify()->Title = "Log error messages";
    LogErrorLevel.modify()->Type = Configuration::Bool;
    LogErrorLevel.modify()->Details = "When enabled errors will be included in the log file. \n\nRecommended Value: On";
    LogErrorLevelVal.modify()->Value = true;
    LogErrorLevel.modify()->ConfigurationBoolDbo.insert(LogErrorLevelVal);

    //LogInfoLevel
    Wt::Dbo::ptr<Configuration> LogInfoLevel = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationBool> LogInfoLevelVal = session.add(new ConfigurationBool());
    LogInfoLevel.modify()->Id.Name = "LogInfoLevel";
    LogInfoLevel.modify()->Id.Application = "Logging";
    LogInfoLevel.modify()->Title = "Log informational notices";
    LogInfoLevel.modify()->Type = Configuration::Bool;
    LogInfoLevel.modify()->Details = "When enabled informational notices will be included in the log file. These notices only gives information rather than reporting a warning or an error.";
    LogInfoLevelVal.modify()->Value = false;
    LogInfoLevel.modify()->ConfigurationBoolDbo.insert(LogInfoLevelVal);

    //LogSecureLevel
    Wt::Dbo::ptr<Configuration> LogSecureLevel = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationBool> LogSecureLevelVal = session.add(new ConfigurationBool());
    LogSecureLevel.modify()->Id.Name = "LogSecureLevel";
    LogSecureLevel.modify()->Id.Application = "Logging";
    LogSecureLevel.modify()->Title = "Log security events";
    LogSecureLevel.modify()->Type = Configuration::Bool;
    LogSecureLevel.modify()->Details = "When enabled security related messages will be included in the log file.\n\nRecommended Value: On";
    LogSecureLevelVal.modify()->Value = true;
    LogSecureLevel.modify()->ConfigurationBoolDbo.insert(LogInfoLevelVal);

    //LogWarnLevel
    Wt::Dbo::ptr<Configuration> LogWarnLevel = session.add(new Configuration());
    Wt::Dbo::ptr<ConfigurationBool> LogWarnLevelVal = session.add(new ConfigurationBool());
    LogWarnLevel.modify()->Id.Name = "LogWarnLevel";
    LogWarnLevel.modify()->Id.Application = "Logging";
    LogWarnLevel.modify()->Title = "Log warnings";
    LogWarnLevel.modify()->Type = Configuration::Bool;
    LogWarnLevel.modify()->Details = "When enabled warnings will be included in the log file. These warnings indicate that there was something could have caused an error and should be considered.\n\nRecommended Value: On";
    LogWarnLevelVal.modify()->Value = true;
    LogWarnLevel.modify()->ConfigurationBoolDbo.insert(LogWarnLevelVal);
    */
    transaction.commit();
}

void uninstall(Wt::Dbo::Session& session) {
    session.dropTables();
}

}

#endif // DBCONFIG_HPP
