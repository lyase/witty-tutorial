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
add_subdirectory(ressource)

add_executable(client client.cpp)
target_link_libraries(client ${ALL_LIBS})

add_executable(server server.cpp )
target_link_libraries(server ressource ${ALL_LIBS})


add_executable(clientfromscratch webclient.cpp)
target_link_libraries(clientfromscratch ${ALL_LIBS})

enable_testing()

# server.key and server.crt were generated via SSL as shown here
# http://www.akadia.com/services/ssh_test_certificate.html
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/server.key)
    message(FATAL_ERROR "server.key does not exist. You must generate it with openssl as shown here: http://www.akadia.com/services/ssh_test_certificate.html. IT MUST BE CHMOD 0600")
endif()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/server.crt)
    message(FATAL_ERROR "server.crt does not exist. You must generate it with openssl as shown here: http://www.akadia.com/services/ssh_test_certificate.html")
endif()

file(COPY test.sh server.key server.crt dh512.pem DESTINATION .)
add_test(clientfromscratch ./test.sh)
