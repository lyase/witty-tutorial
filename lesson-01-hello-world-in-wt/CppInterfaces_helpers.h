//
// CppInterfaces.h
//

#define Interface class

#define DeclareInterface(name)\
 Interface name { \
          public: \
          virtual ~name() {}; // breaks if set as pure virtual =0

//#define DeclareBasedInterface(name, base) class name :\
        public base { \
           public: \
           virtual ~name() {}


#define implements public
#define EndInterface };
