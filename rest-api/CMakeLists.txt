project (api)

cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

add_definitions(-std=c++11)

find_package(Boost COMPONENTS system thread signals unit_test_framework filesystem program_options)
find_library(wt NAMES wtd wt)
find_library(wthttp NAMES wthttpd wthttp)

set(ALL_LIBS ${wt} ${wthttp}
    ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY})

add_executable(client client.cpp)
target_link_libraries(client ${ALL_LIBS})

add_executable(server server.cpp)
target_link_libraries(server ${ALL_LIBS})

add_executable(test_conn test.cpp)
target_link_libraries(test_conn ${ALL_LIBS})

enable_testing()
add_test(client client)
