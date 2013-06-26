project (api)

cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

find_package(Boost COMPONENTS system thread signals unit_test_framework filesystem program_options)
find_library(wt NAMES wtd wt)
find_library(wthttp NAMES wthttpd wthttp)

add_executable(client client.cpp)
target_link_libraries(client ${wt} ${wthttp}
    ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY})

add_executable(server server.cpp)
target_link_libraries(server ${wt} ${wthttp}
    ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY})
