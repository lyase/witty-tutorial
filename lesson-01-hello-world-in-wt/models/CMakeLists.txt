project ("models")      # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:project
find_library(wtdbosqlite3 wtdbosqlite3)
add_library(models User.cpp Yahoo.cpp dbinfo.cpp dbinfo.hpp)
target_link_libraries(models    ${wthttp} ${wtdbo} ${wtdbosqlite3} ${wt}
    ${hpdf}
    ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)
