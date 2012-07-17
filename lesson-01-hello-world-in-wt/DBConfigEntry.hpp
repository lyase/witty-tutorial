#ifndef DBCONFIG_HPP
#define DBCONFIG_HPP

#include <string>
#include <Wt/Dbo/Dbo>

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

    DBConfigEntry(const std::string& key, const std::string& value) :
        key(key), asString(value), valueType(vtString) {}

    DBConfigEntry(const std::string& key, double value) :
        key(key), asDouble(value), valueType(vtDouble) {}

    DBConfigEntry(const std::string& key, int value) :
        key(key), asInt(value), valueType(vtInt) {}
        //  this will convert to int a boolean key
        // beware the convertion will depend on compiler
    DBConfigEntry(const std::string& key, bool value) :
        key(key), asInt(value != 0), valueType(vtInt) {}

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
};

#endif // DBCONFIG_HPP
