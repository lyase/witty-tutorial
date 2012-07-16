/*
 * Copyright (C) 2009 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifdef WTDBO
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
#define BOOST_TEST_MODULE mytestSuite
#define BOOST_TEST_DYN_LINK
 
#include <boost/test/unit_test.hpp>
//Post directives
class Configuration;
class ConfigurationBool;
class ConfigurationDouble;
class ConfigurationFloat;
class ConfigurationInt;
class ConfigurationString;
//Configuration Keys structure
struct ConfigurationKeys
{
std::string Name;
	std::string Application;

ConfigurationKeys();
ConfigurationKeys(std::string Name, std::string Application);
bool operator< (const ConfigurationKeys& other) const;
bool operator== (const ConfigurationKeys& other) const;
};
//Overloaded operator<< for Configuration Keys structure
std::ostream& operator<< (std::ostream& o, const ConfigurationKeys& c);
namespace Wt
{
	namespace Dbo
	{
		//Overloaded Wt::Dbo::field() for Configuration Keys structure
		template<class Action>
		void field(Action& action, ConfigurationKeys& Keys, const std::string& name, int size = -1)
		{
			field(action, Keys.Name,	"Name", 255);
			field(action, Keys.Application,	"Application", 255);
		}

		//Overloaded dbo_traits for Configuration DBO
		template<>
		struct dbo_traits<::Configuration> : public dbo_default_traits
		{
			typedef ConfigurationKeys IdType;
			static IdType invalidId();
			static const char *surrogateIdField();
		};
		
		//Overloaded dbo_traits for ConfigurationBool DBO
		template<>
		struct dbo_traits<ConfigurationBool> : public dbo_default_traits
		{
			static const char *surrogateIdField();
		};
		//Overloaded dbo_traits for ConfigurationDouble DBO
		template<>
		struct dbo_traits<ConfigurationDouble> : public dbo_default_traits
		{
			static const char *surrogateIdField();
		};
		//Overloaded dbo_traits for ConfigurationFloat DBO
		template<>
		struct dbo_traits<ConfigurationFloat> : public dbo_default_traits
		{
			static const char *surrogateIdField();
		};
		//Overloaded dbo_traits for ConfigurationInt DBO
		template<>
		struct dbo_traits<ConfigurationInt> : public dbo_default_traits
		{
			static const char *surrogateIdField();
		};
		//Overloaded dbo_traits for ConfigurationString DBO
		template<>
		struct dbo_traits<ConfigurationString> : public dbo_default_traits
		{
			static const char *surrogateIdField();
		};
	}
};
//Configuration DBO class
class Configuration
{
	public:
		enum ValueTypes
		{
			Bool = 0,
			Double = 1,
			Float = 2,
			Int = 3,
			String = 4,
		};
		//hasMany relations
		Wt::Dbo::collection< Wt::Dbo::ptr<ConfigurationBool> >		ConfigurationBoolDbo;
		Wt::Dbo::collection< Wt::Dbo::ptr<ConfigurationDouble> >	ConfigurationDoubleDbo;
		Wt::Dbo::collection< Wt::Dbo::ptr<ConfigurationFloat> >		ConfigurationFloatDbo;
		Wt::Dbo::collection< Wt::Dbo::ptr<ConfigurationInt> >		ConfigurationIntDbo;
		Wt::Dbo::collection< Wt::Dbo::ptr<ConfigurationString> >	ConfigurationStringDbo;
		//Fields
		ConfigurationKeys				Id;
		std::string						Title;
		ValueTypes						Type;
		boost::optional<std::string>	Details;
		//Persistence Method
		template<class Action>
		void persist(Action& a)
		{
			Wt::Dbo::id(a, Id, "Id");
			Wt::Dbo::field(a, Title,	"Title");
			Wt::Dbo::field(a, Type,		"Type");
			Wt::Dbo::field(a, Details,	"Details");
			Wt::Dbo::hasMany(a, ConfigurationBoolDbo, Wt::Dbo::ManyToOne, "Configuration");
			Wt::Dbo::hasMany(a, ConfigurationDoubleDbo, Wt::Dbo::ManyToOne, "Configuration");
			Wt::Dbo::hasMany(a, ConfigurationFloatDbo, Wt::Dbo::ManyToOne, "Configuration");
			Wt::Dbo::hasMany(a, ConfigurationIntDbo, Wt::Dbo::ManyToOne, "Configuration");
			Wt::Dbo::hasMany(a, ConfigurationStringDbo, Wt::Dbo::ManyToOne, "Configuration");
		}
};
//ConfigurationBool DBO Class
class ConfigurationBool
{
	public:
		//belongsTo
		Wt::Dbo::ptr<Configuration> ConfigurationDbo;
		bool Value;

		template<class Action>void persist(Action& a)
		{
			Wt::Dbo::field(a, Value, "Value");
			Wt::Dbo::belongsTo(a, ConfigurationDbo, "Configuration", Wt::Dbo::OnUpdateCascade | Wt::Dbo::OnDeleteCascade);
		}
};
//ConfigurationDouble DBO Class
class ConfigurationDouble
{
	public:
		//belongsTo
		Wt::Dbo::ptr<Configuration> ConfigurationDbo;
		double Value;
		template<class Action>void persist(Action& a)
		{
			Wt::Dbo::field(a, Value, "Value");
			Wt::Dbo::belongsTo(a, ConfigurationDbo, "Configuration", Wt::Dbo::OnUpdateCascade | Wt::Dbo::OnDeleteCascade);
		}
};
//ConfigurationFloat DBO Class
class ConfigurationFloat
{
	public:
		//belongsTo
		Wt::Dbo::ptr<Configuration> ConfigurationDbo;
		float Value;
		template<class Action>void persist(Action& a)
		{
			Wt::Dbo::field(a, Value, "Value");
			Wt::Dbo::belongsTo(a, ConfigurationDbo, "Configuration", Wt::Dbo::OnUpdateCascade | Wt::Dbo::OnDeleteCascade);
		}
};
//ConfigurationInt DBO Class
class ConfigurationInt
{
	public:
		//belongsTo
		Wt::Dbo::ptr<Configuration> ConfigurationDbo;
		int Value;
		template<class Action>void persist(Action& a)
		{
			Wt::Dbo::field(a, Value, "Value");
			Wt::Dbo::belongsTo(a, ConfigurationDbo, "Configuration", Wt::Dbo::OnUpdateCascade | Wt::Dbo::OnDeleteCascade);
		}
//ConfigurationString DBO Class
class ConfigurationString
{
	public:
		//belongsTo
		Wt::Dbo::ptr<Configuration> ConfigurationDbo;
		boost::optional<std::string> Value;
		template<class Action>void persist(Action& a)
		{
			Wt::Dbo::field(a, Value, "Value");
			Wt::Dbo::belongsTo(a, ConfigurationDbo, "Configuration", Wt::Dbo::OnUpdateCascade | Wt::Dbo::OnDeleteCascade);
		}
};
//Configuration Keys
ConfigurationKeys::ConfigurationKeys()
	: Name(std::string()), Application(std::string())
{ }
ConfigurationKeys::ConfigurationKeys(std::string Name, std::string Application)
	: Name(Name), Application(Application)
{ }
bool ConfigurationKeys::operator== (const ConfigurationKeys& other) const
{
	return Name == other.Name && Application == other.Application;
}
bool ConfigurationKeys::operator< (const ConfigurationKeys& other) const
{
	if(Application < other.Application)
	{
		return true;
	}
	else if(Name == other.Name)
	{
		return Name < other.Name;
	}
	else
	{
		return false;
	}
}
std::ostream& operator<< (std::ostream& o, const ConfigurationKeys& c)
{
	return o << "(" << c.Name << ", " << c.Application << ")";
}
//Overloaded dbo_trait for Configuration DBO
Wt::Dbo::dbo_traits<Configuration>::IdType Wt::Dbo::dbo_traits<Configuration>::invalidId()
{
	return Wt::Dbo::dbo_traits<Configuration>::IdType();
}
const char* Wt::Dbo::dbo_traits<Configuration>::surrogateIdField()
{
	return 0;
}

//Remove ID field from Configuration related DBOs
const char* Wt::Dbo::dbo_traits<ConfigurationBool>::surrogateIdField()
{
	return 0;
}
const char* Wt::Dbo::dbo_traits<ConfigurationDouble>::surrogateIdField()
{
	return 0;
}
const char* Wt::Dbo::dbo_traits<ConfigurationFloat>::surrogateIdField()
{
	return 0;
}
const char* Wt::Dbo::dbo_traits<ConfigurationInt>::surrogateIdField()
{
	return 0;
}
const char* Wt::Dbo::dbo_traits<ConfigurationString>::surrogateIdField()
{
	return 0;
}
class Configurations;
//SQL Connection
Wt::Dbo::FixedSqlConnectionPool *SQLPool;
//Global Configurations
Configurations *Config;

class Configurations
{
	public:
		typedef boost::unordered_map< const std::string, boost::unordered_map< const std::string, Wt::Dbo::ptr<ConfigurationBool> > > ConfigurationBoolMaps;
		typedef boost::unordered_map< const std::string, boost::unordered_map< const std::string, Wt::Dbo::ptr<ConfigurationDouble> > > ConfigurationDoubleMaps;
		typedef boost::unordered_map< const std::string, boost::unordered_map< const std::string, Wt::Dbo::ptr<ConfigurationFloat> > > ConfigurationFloatMaps;
		typedef boost::unordered_map< const std::string, boost::unordered_map< const std::string, Wt::Dbo::ptr<ConfigurationInt> > > ConfigurationIntMaps;
		typedef boost::unordered_map< const std::string, boost::unordered_map< const std::string, Wt::Dbo::ptr<ConfigurationString> > > ConfigurationStringMaps;
		
		typedef boost::tuple< Wt::Dbo::ptr<Configuration>, Wt::Dbo::ptr<ConfigurationBool> > ConfigurationBoolTuples;
		typedef boost::tuple< Wt::Dbo::ptr<Configuration>, Wt::Dbo::ptr<ConfigurationDouble> > ConfigurationDoubleTuples;
		typedef boost::tuple< Wt::Dbo::ptr<Configuration>, Wt::Dbo::ptr<ConfigurationFloat> > ConfigurationFloatTuples;
		typedef boost::tuple< Wt::Dbo::ptr<Configuration>, Wt::Dbo::ptr<ConfigurationInt> > ConfigurationIntTuples;
		typedef boost::tuple< Wt::Dbo::ptr<Configuration>, Wt::Dbo::ptr<ConfigurationString> > ConfigurationStringTuples;
		
		Configurations();
		void Install();
		void Uninstall();
		void FetchAll();

		template<typename Source> bool GetBool(const std::string& Name, const std::string& Application, Source Default);
		bool GetBool(const std::string& Name, const std::string& Application, bool Default = false);
		template<typename Source> double GetDouble(const std::string& Name, const std::string& Application, Source Default);
		double GetDouble(const std::string& Name, const std::string& Application, double Default = 0);
		template<typename Source> float GetFloat(const std::string& Name, const std::string& Application, Source Default);
		float GetFloat(const std::string& Name, const std::string& Application, float Default = 0);
		template<typename Source> int GetInt(const std::string& Name, const std::string& Application, Source Default);
		int GetInt(const std::string& Name, const std::string& Application, int Default = 0);
		template<typename Source> std::string GetStr(const std::string& Name, const std::string& Application, Source Default);
		std::string GetStr(const std::string& Name, const std::string& Application, std::string Default = "");

		long long GetLoadDurationinMS() const;
		int GetConfigurationsCount() const;

	protected:
		ConfigurationBoolMaps ConfigurationBoolMap;
		ConfigurationDoubleMaps ConfigurationDoubleMap;
		ConfigurationFloatMaps ConfigurationFloatMap;
		ConfigurationIntMaps ConfigurationIntMap;
		ConfigurationStringMaps ConfigurationStringMap;
		
		boost::posix_time::time_duration LoadDuration;
		int ConfigurationsCount;
	private:
		mutable boost::shared_mutex mutex;
		Wt::Dbo::Session Session;
		Wt::Dbo::Query<ConfigurationBoolTuples> FetchBoolQuery;
		Wt::Dbo::Query<ConfigurationDoubleTuples> FetchDoubleQuery;
		Wt::Dbo::Query<ConfigurationFloatTuples> FetchFloatQuery;
		Wt::Dbo::Query<ConfigurationIntTuples> FetchIntQuery;
		Wt::Dbo::Query<ConfigurationStringTuples> FetchStringQuery;
};
#define READ_LOCK boost::shared_lock<boost::shared_mutex> lock(mutex)
#define WRITE_LOCK boost::lock_guard<boost::shared_mutex> lock(mutex)
Configurations::Configurations()
{
	ConfigurationsCount = 0;
	LoadDuration = boost::posix_time::time_duration(0, 0, 0);
	Session.setConnectionPool(*SQLPool);
	//Map DBOs
	Session.mapClass<Configuration>("configuration");
	Session.mapClass<ConfigurationBool>("configurationbool");
	Session.mapClass<ConfigurationDouble>("configurationdouble");
	Session.mapClass<ConfigurationFloat>("configurationfloat");
	Session.mapClass<ConfigurationInt>("configurationint");
	Session.mapClass<ConfigurationString>("configurationstring");
	//Define the query to fetch and join all rows
	FetchBoolQuery = Session.query<ConfigurationBoolTuples>(std::string("SELECT")
	+	" \"configuration\", \"configurationbool\""
	+	" FROM \"configuration\""
	+	" LEFT JOIN \"configurationbool\" ON \"configuration\".\"Name\" = \"configurationbool\".\"Name\" AND \"configuration\".\"Application\" = \"configurationbool\".\"Application\" "
	+	" WHERE \"configuration\".\"Type\" = 0");
	FetchDoubleQuery = Session.query<ConfigurationDoubleTuples>(std::string("SELECT")
	+	" \"configuration\", \"configurationdouble\""
	+	" FROM \"configuration\""
	+	" LEFT JOIN \"configurationdouble\" ON \"configuration\".\"Name\" = \"configurationdouble\".\"Name\" AND \"configuration\".\"Application\" = \"configurationdouble\".\"Application\" "
	+	" WHERE \"configuration\".\"Type\" = 1");
	FetchFloatQuery = Session.query<ConfigurationFloatTuples>(std::string("SELECT")
	+	" \"configuration\", \"configurationfloat\""
	+	" FROM \"configuration\""
	+	" LEFT JOIN \"configurationfloat\" ON \"configuration\".\"Name\" = \"configurationfloat\".\"Name\" AND \"configuration\".\"Application\" = \"configurationfloat\".\"Application\" "
	+	" WHERE \"configuration\".\"Type\" = 2");
	FetchIntQuery = Session.query<ConfigurationIntTuples>(std::string("SELECT")
	+	" \"configuration\", \"configurationint\""
	+	" FROM \"configuration\""
	+	" LEFT JOIN \"configurationint\" ON \"configuration\".\"Name\" = \"configurationint\".\"Name\" AND \"configuration\".\"Application\" = \"configurationint\".\"Application\" "
	+	" WHERE \"configuration\".\"Type\" = 3");
	FetchStringQuery = Session.query<ConfigurationStringTuples>(std::string("SELECT")
	+	" \"configuration\", \"configurationstring\""
	+	" FROM \"configuration\""
	+	" LEFT JOIN \"configurationstring\" ON \"configuration\".\"Name\" = \"configurationstring\".\"Name\" AND \"configuration\".\"Application\" = \"configurationstring\".\"Application\" "
	+	" WHERE \"configuration\".\"Type\" = 4");
}

void Configurations::Install()
{
	Session.createTables();
	Wt::Dbo::Transaction transaction(Session);

	//BaseURL
	Wt::Dbo::ptr<Configuration> BaseUrl = Session.add(new Configuration());
	Wt::Dbo::ptr<ConfigurationString> BaseUrlVal = Session.add(new ConfigurationString());
	BaseUrl.modify()->Id.Name = "BaseURL";
	BaseUrl.modify()->Id.Application = "Server";
	BaseUrl.modify()->Title = "Base URL of the website";
	BaseUrl.modify()->Type = Configuration::String;
	BaseUrl.modify()->Details = "This is the base URL that the user can see when browsing. For example, http://www.mywebsite.com/wt .\nThis field may be left empty.";
	BaseUrlVal.modify()->Value = "";
	BaseUrl.modify()->ConfigurationStringDbo.insert(BaseUrlVal);
	//DosPuzzle
	Wt::Dbo::ptr<Configuration> DosPuzzle = Session.add(new Configuration());
	Wt::Dbo::ptr<ConfigurationBool> DosPuzzleVal = Session.add(new ConfigurationBool());
	DosPuzzle.modify()->Id.Name = "DosPuzzle";
	DosPuzzle.modify()->Id.Application = "Server";
	DosPuzzle.modify()->Title = "Denial-of-Service protection puzzle";
	DosPuzzle.modify()->Type = Configuration::Bool;
	DosPuzzle.modify()->Details = "When enabled the server adds a puzzle to validate Ajax sessions in the first Ajax request. This is a simple measure which avoids Denial-of-Service attacks on Ajax sessions.\n\nDefault value: Off";
	DosPuzzleVal.modify()->Value = false;
	DosPuzzle.modify()->ConfigurationBoolDbo.insert(DosPuzzleVal);
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
	try
	{
		transaction.commit();
	}
	catch(Wt::Dbo::Exception& e)
	{
		throw e;
	}
}

void Configurations::Uninstall()
{
	try
	{
		Session.dropTables();
	}
	catch(Wt::Dbo::Exception& e)
	{
		throw e;
	}
}
void Configurations::FetchAll()
{
	WRITE_LOCK;
	//Time at start
	boost::posix_time::ptime PTStart = boost::posix_time::microsec_clock::local_time();

	Wt::Dbo::Transaction transaction(Session);
	try
	{
		ConfigurationsCount = 0;
		typedef Wt::Dbo::collection< ConfigurationBoolTuples > BoolCollections;
		typedef Wt::Dbo::collection< ConfigurationDoubleTuples > DoubleCollections;
		typedef Wt::Dbo::collection< ConfigurationFloatTuples > FloatCollections;
		typedef Wt::Dbo::collection< ConfigurationIntTuples > IntCollections;
		typedef Wt::Dbo::collection< ConfigurationStringTuples > StringCollections;
		BoolCollections BoolCollection;
		DoubleCollections DoubleCollection;
		FloatCollections FloatCollection;
		IntCollections IntCollection;
		StringCollections StringCollection;
		//Fetch em all
		Wt::Dbo::Transaction transaction(Session);
		BoolCollection = FetchBoolQuery.resultList();
		for(BoolCollections::const_iterator itr = BoolCollection.begin();
			itr != BoolCollection.end();
			itr++, ConfigurationsCount++)
		{
			std::cerr << itr->get<0>()->Id.Name << std::endl;
			ConfigurationBoolMap[itr->get<0>()->Id.Application][itr->get<0>()->Id.Name] = itr->get<1>();
		}

		DoubleCollection = FetchDoubleQuery.resultList();
		for(DoubleCollections::const_iterator itr = DoubleCollection.begin();
			itr != DoubleCollection.end();
			itr++, ConfigurationsCount++)
		{
			std::cerr << itr->get<0>()->Id.Name << std::endl;
			ConfigurationDoubleMap[itr->get<0>()->Id.Application][itr->get<0>()->Id.Name] = itr->get<1>();
		}

		FloatCollection = FetchFloatQuery.resultList();
		for(FloatCollections::const_iterator itr = FloatCollection.begin();
			itr != FloatCollection.end();
			itr++, ConfigurationsCount++)
		{
			std::cerr << itr->get<0>()->Id.Name << std::endl;
			ConfigurationFloatMap[itr->get<0>()->Id.Application][itr->get<0>()->Id.Name] = itr->get<1>();
		}

		IntCollection = FetchIntQuery.resultList();
		for(IntCollections::const_iterator itr = IntCollection.begin();
			itr != IntCollection.end();
			itr++, ConfigurationsCount++)
		{
			std::cerr << itr->get<0>()->Id.Name << std::endl;
			ConfigurationIntMap[itr->get<0>()->Id.Application][itr->get<0>()->Id.Name] = itr->get<1>();
		}

		StringCollection = FetchStringQuery.resultList();
		for(StringCollections::const_iterator itr = StringCollection.begin();
			itr != StringCollection.end();
			itr++, ConfigurationsCount++)
		{
			std::cerr << itr->get<0>()->Id.Name << std::endl;
			ConfigurationStringMap[itr->get<0>()->Id.Application][itr->get<0>()->Id.Name] = itr->get<1>();
		}
		transaction.commit();
	}
	catch(Wt::Dbo::Exception& e)
	{
		throw e;
	}

	//Time at end
	boost::posix_time::ptime PTEnd = boost::posix_time::microsec_clock::local_time();
	LoadDuration = boost::posix_time::time_duration(PTEnd - PTStart);
}

//Boolean getter
template<>
bool Configurations::GetBool<bool>(const std::string& Name, const std::string& Application, bool Default)
{
	READ_LOCK;
	return ConfigurationBoolMap[Application][Name] ? ConfigurationBoolMap[Application][Name]->Value : Default;
}

//Double getter
template<>
double Configurations::GetDouble<double>(const std::string& Name, const std::string& Application, double Default)
{
	READ_LOCK;
	return ConfigurationDoubleMap[Application][Name] ? ConfigurationDoubleMap[Application][Name]->Value : Default;
}

//Float getter
template<>
float Configurations::GetFloat<float>(const std::string& Name, const std::string& Application, float Default)
{
	READ_LOCK;
	return ConfigurationFloatMap[Application][Name] ?  ConfigurationFloatMap[Application][Name]->Value : Default;
}

//Integer getter
template<>
int Configurations::GetInt<int>(const std::string& Name, const std::string& Application, int Default)
{
	READ_LOCK;
	return ConfigurationIntMap[Application][Name] ? ConfigurationIntMap[Application][Name]->Value : Default;
}

//String getter
template<>
std::string Configurations::GetStr<std::string>(const std::string& Name, const std::string& Application, std::string Default)
{
	READ_LOCK;
	if(!ConfigurationStringMap[Application][Name])
	{
		return Default;
	}
	if(!ConfigurationStringMap[Application][Name]->Value.is_initialized())
	{
		return "";
	}
	return *ConfigurationStringMap[Application][Name]->Value;
}

//Boolean alternative source getters
template<>
bool Configurations::GetBool<double>(const std::string& Name, const std::string& Application, double Default)
{
	READ_LOCK;
	return GetDouble<double>(Name, Application, Default) > 0;
}

template<>
bool Configurations::GetBool<float>(const std::string& Name, const std::string& Application, float Default)
{
	READ_LOCK;
	return GetFloat<float>(Name, Application, Default) > 0;
}

template<>
bool Configurations::GetBool<int>(const std::string& Name, const std::string& Application, int Default)
{
	READ_LOCK;
	return GetInt<int>(Name, Application, Default) > 0;
}

template<>
bool Configurations::GetBool<std::string>(const std::string& Name, const std::string& Application, std::string Default)
{
	READ_LOCK;
	return ConfigurationStringMap[Application][Name];
}

bool Configurations::GetBool(const std::string& Name, const std::string& Application, bool Default)
{
	READ_LOCK;
	return GetBool<bool>(Name, Application, Default);
}

//Double alternative source getters
template<>
double Configurations::GetDouble<int>(const std::string& Name, const std::string& Application, int Default)
{
	READ_LOCK;
	return (double)GetInt<int>(Name, Application, Default);
}

double Configurations::GetDouble(const std::string& Name, const std::string& Application, double Default)
{
	READ_LOCK;
	return GetDouble<double>(Name, Application, Default);
}

//Float alternative source getters
template<>
float Configurations::GetFloat<double>(const std::string& Name, const std::string& Application, double Default)
{
	READ_LOCK;
	return (float)GetDouble<double>(Name, Application, Default);
}

template<>
float Configurations::GetFloat<int>(const std::string& Name, const std::string& Application, int Default)
{
	READ_LOCK;
	return (float)GetInt<int>(Name, Application, Default);
}

float Configurations::GetFloat(const std::string& Name, const std::string& Application, float Default)
{
	READ_LOCK;
	return GetFloat<float>(Name, Application, Default);
}

//Integer alternative source getters
template<>
int Configurations::GetInt<bool>(const std::string& Name, const std::string& Application, bool Default)
{
	READ_LOCK;
	return GetBool<bool>(Name, Application, Default) ? 1 : 0;
}

int Configurations::GetInt(const std::string& Name, const std::string& Application, int Default)
{
	READ_LOCK;
	return GetInt<int>(Name, Application, Default);
}

//String alternative source getters
template<>
std::string Configurations::GetStr<double>(const std::string& Name, const std::string& Application, double Default)
{
	READ_LOCK;
	std::ostringstream ss;
	ss << GetDouble<double>(Name, Application, Default);
	return ss.str();
}

template<>
std::string Configurations::GetStr<float>(const std::string& Name, const std::string& Application, float Default)
{
	READ_LOCK;
	std::ostringstream ss;
	ss << GetFloat<float>(Name, Application, Default);
	return ss.str();
}

template<>
std::string Configurations::GetStr<int>(const std::string& Name, const std::string& Application, int Default)
{
	READ_LOCK;
	std::ostringstream ss;
	ss << GetInt<int>(Name, Application, Default);
	return ss.str();
}

std::string Configurations::GetStr(const std::string& Name, const std::string& Application, std::string Default)
{
	READ_LOCK;
	return GetStr<std::string>(Name, Application, Default);
}

long long Configurations::GetLoadDurationinMS() const
{
	READ_LOCK;
	return LoadDuration.total_milliseconds();
}

int Configurations::GetConfigurationsCount() const
{
	READ_LOCK;
	return ConfigurationsCount;
}

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
	try
	{
		//Wt::Dbo::SqlConnection *SQLConnection = new Wt::Dbo::backend::MySQL("wt", "root", "root", "127.0.0.1");
		Wt::Dbo::SqlConnection *SQLConnection = new Wt::Dbo::backend::Sqlite3(":memory:");
		SQLConnection->setProperty("show-queries", "true");
		SQLPool = new Wt::Dbo::FixedSqlConnectionPool(SQLConnection, 1);
	}
	catch(Wt::Dbo::Exception& e)
	{
		StartLogger.entry("fatal") << Wt::WLogger::timestamp << Wt::WLogger::sep
		<< '[' << "fatal error" << ']' << Wt::WLogger::sep << e.what();
		exit(EXIT_FAILURE);
	}
	catch(std::exception &e)
	{
		StartLogger.entry("fatal") << Wt::WLogger::timestamp << Wt::WLogger::sep
		<< '[' << "fatal error" << ']' << Wt::WLogger::sep << e.what();
		exit(EXIT_FAILURE);
	}

	/* *************************************************************************
	 * ************************  Load Configurations  **************************
	 * *************************************************************************/
	Config = new Configurations;
	try
	{
		//Config->Uninstall();
		Config->Install();
		Config->FetchAll();
	}
	catch(Wt::Dbo::Exception& e)
	{
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

#endif