project (lesson05-auth)

cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11 -Wall -Wextra)

find_package(Boost COMPONENTS system thread signals unit_test_framework filesystem program_options)
find_library(HPDF hpdf)
find_library(WT NAMES wtd wt)
find_library(WTHTTP NAMES wthttpd wthttp)
find_library(WTDBO NAMES wtdbod wtdbo)
find_library(WTDBOSQLITE3 NAMES wtdbosqlite3d wtdbosqlite3)

add_library(lesson-05-authlib STATIC App.cpp Session.cpp Services.cpp User.hpp Services.hpp)
target_link_libraries(lesson-05-authlib
    ${Boost_SYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${Boost_THREAD_LIBRARY}
    ${WT} ${WTHTTP} ${WTDBO} ${WTDBOSQLITE3})

add_executable(lesson-05-auth main.cpp)
target_link_libraries(lesson-05-auth lesson-05-authlib)

file(COPY debug.sh DESTINATION .)
file(COPY run.sh DESTINATION .)
file(COPY wt-config.xml DESTINATION .)
