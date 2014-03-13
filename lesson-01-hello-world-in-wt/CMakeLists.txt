
message("* Adding build types...")

SET(GCC_DEBUG_FLAGS "-g -Wall")
SET(CMAKE_CXX_FLAGS_COVERAGE "${GCC_DEBUG_FLAGS} -fprofile-arcs -ftest-coverage" CACHE STRING "Flags used by the C++ compiler during coverage builds." FORCE )
SET(CMAKE_C_FLAGS_COVERAGE "${GCC_DEBUG_FLAGS} -fprofile-arcs -ftest-coverage" CACHE STRING "Flags used by the C compiler during coverage builds." FORCE )
SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "" CACHE STRING "Flags used for linking binaries during coverage builds."                    FORCE )
SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "" CACHE STRING "Flags used by the shared libraries linker during coverage builds."              FORCE )
MARK_AS_ADVANCED( CMAKE_CXX_FLAGS_COVERAGE
                  CMAKE_C_FLAGS_COVERAGE
                  CMAKE_EXE_LINKER_FLAGS_COVERAGE
                  CMAKE_SHARED_LINKER_FLAGS_COVERAGE )
# This is the cmake file. It describes how to build our app
# The documentation for how to build these can be found here:
#   http://www.cmake.org/cmake/help/cmake-2-8-docs.html

# CMake likes us to put this here in case someone tries to read this file with an older version of cmake
cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

# Sets the name of the project. Additionally this sets the variables <projectName>_BINARY_DIR and <projectName>_SOURCE_DIR to the respective values.
project ("hello world in wt++")      # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:project

#add_definitions(-std=c++11)
add_definitions(-std=c++0x)
# Other Libraries
find_package(Boost COMPONENTS system thread signals unit_test_framework filesystem program_options)
find_library(hpdf hpdf)
find_library(wt wt)
find_library(wthttp wthttp)
find_library(wtdbo wtdbo)
find_library(wtdbosqlite3 wtdbosqlite3)

# Debug mode
option(DEBUG "Run witty in debug mode ?" OFF)
set(DB_CONNECTION_STRING "blog.db" CACHE string "The connection info to connect to your database driver of choice")
set(LOG_FILE_NAME "blog.log" CACHE string "Where to log to")
if (${DEBUG})
    set(DEBUG_VALUE true)
    set(LOG_LINE "*")
else()
    set(DEBUG_VALUE false)
    set(LOG_LINE "* -debug")
endif()
CONFIGURE_FILE(wt-config.xml wt-config.xml)


# Models Library
add_subdirectory(models)
add_subdirectory(Auth)
# Main Library
add_library(helloWorld HelloApp.cpp MainWindow.cpp AskWindow.cpp SayWindow.cpp AdminWindow.cpp CsvUtil.C)
target_link_libraries(helloWorld models Auth)

# docroot stuff
file(COPY run.sh debug.sh DESTINATION .)
file(COPY resources DESTINATION .)
file(COPY timeseries.csv DESTINATION .)


# This tells cmake that we want to create an executable called 'hellowt' and the source files are just 'main.cpp'
#setting the source files of the project one by one.
add_executable(hellowt main.cpp )
configure_file(hellowt.xml.in hellowt.xml)
target_link_libraries(hellowt
    helloWorld
    ${wthttp} ${wtdbo} ${wtdbosqlite3} ${wt} 
    ${hpdf}
    ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)
#------------------------------------------------------------------------------------------------------

#------------------------------------------------------------------------------------------------------
# Tests
enable_testing()

add_subdirectory(tests)

#------------------------------------------------------------------------------------------------------
# Deploy

# This will generate a 'doc' folder in the source directory, then move it to
# the build directory under 'generatedStatic'
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generatedStatic"
    COMMAND doxygen doxy.config 
    COMMAND mkdir ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic
    COMMAND mv doc ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic/
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(doc DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic)

set(SERVER_LINK "desafder@192.168.10.21" CACHE string 
    "The scp destination base for the 'make install' target")
set(SERVER_PATH "~/hello" CACHE string 
    "The scp destination directory for the 'make install' target")

if (${SERVER_PATH} STREQUAL "")
    set(SERVER_PATH .)
endif()

set(SERVER_DEST ${SERVER_LINK}:${SERVER_PATH})
configure_file(cmdl.in cmdl)

# In order to use the 'install' command you need passwordless ssh access to the
# 'SERVER_LINK'. You can optain this by generating ssh keys and uploading them
# to the server.
#
# On your development computer, generate some ssh keys:
#   ssh-keygen  
#
# On your deployment server, put the contents of id_rsa.pub on a line on its own in ~/.ssh/authorized_keys.
# If that file is empty, you could just copy it there. Maybe the easiest way is
# to 'cat' it on the dev machine and copy and paste it on the dev machine:
#   LOCAL $ cat ~/.ssh/id_rsa
# .. then copy and paste that line ..
#   SERVER $ cat >> ~/.ssh/authorized_hosts
# .. then paste it there and ctrl+d to finish ..
add_custom_target(install
    COMMAND ssh ${SERVER_LINK} "mkdir -p ${SERVER_PATH}" 
    COMMAND scp cmdl ${SERVER_DEST}
    COMMAND ssh ${SERVER_LINK} "chmod u+x ${SERVER_PATH}/cmdl" 
    COMMAND ssh ${SERVER_LINK} "${SERVER_PATH}/cmdl stop" 
    COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/hellowt ${SERVER_DEST}
    COMMAND scp hellowt.xml ${SERVER_DEST}
    COMMAND scp -r generatedStatic ${SERVER_DEST}
    COMMAND scp wt-config.xml ${SERVER_DEST}
    COMMAND ssh ${SERVER_LINK} "${SERVER_PATH}/cmdl start" 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic
            ${CMAKE_CURRENT_BINARY_DIR}/hellowt 
            ${CMAKE_CURRENT_BINARY_DIR}/hellowt.xml 
            ${CMAKE_CURRENT_BINARY_DIR}/wt-config.xml
            ${CMAKE_CURRENT_BINARY_DIR}/cmdl
)

