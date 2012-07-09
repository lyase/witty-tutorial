# This is the cmake file. It describes how to build our app
# The documentation for how to build these can be found here:
#   http://www.cmake.org/cmake/help/cmake-2-8-docs.html

# CMake likes us to put this here in case someone tries to read this file with an older version of cmake
cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

# Sets the name of the project. Additionally this sets the variables <projectName>_BINARY_DIR and <projectName>_SOURCE_DIR to the respective values.
project ("hello world in wt++")      # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:project
# Other Libraries
find_package(Boost COMPONENTS system thread signals unit_test_framework filesystem)
find_library(wt wt)
find_library(wthttp wthttp)
find_library(wtdbo wtdbo)
find_library(wtdbosqlite3 wtdbosqlite3)
# This tells cmake that we want to create an executable called 'hello' and the source files are just 'main.cpp'
#setting the source files of the project one by one.
SET(hellowt_src  )
SET(hellowt_src ${hellowt_src} main.cpp)
SET(hellowt_src ${hellowt_src} MainWindow.cpp  HelloApp.cpp AskWindow.cpp SayWindow.cpp AdminWindow.cpp FactoryHelloWorldWebsite.hpp )
SET(hellowt_src ${hellowt_src} User.cpp)
# or add all cpp files  to source file list  
#FILE(GLOB ALL_CPP_SRCS *.cpp)
#SET(hellowt_src ${hellowt_src} ${ALL_CPP_SRCS})
add_executable(hellowt ${hellowt_src} )
configure_file(hellowt.xml.in hellowt.xml)
target_link_libraries(hellowt
		      ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
		      ${wt} ${wthttp})
#------------------------------------------------------------------------------------------------------

#------------------------------------------------------------------------------------------------------



#------------------------------------------------------------------------------------------------------
# Tests
enable_testing()

add_subdirectory(tests)
