project(tests)

project(tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing

CONFIGURE_FILE(wt-config.xml wt-config.xml)

find_library(wttest wttest)

add_executable(test_user_set_name ../User.cpp test_user_is_not_mike.cpp)
find_package(Boost COMPONENTS system filesystem REQUIRED)

TARGET_LINK_LIBRARIES(test_user_set_name )
add_test(NAME test_user_set_name 
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         COMMAND ./test_user_set_name)

add_executable(test_user_full ../User.cpp ../testUser_Class_dbo.cpp ../listing.cpp)
TARGET_LINK_LIBRARIES(test_user_full ${wt} ${wtdbo} ${wtdbosqlite3} ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}  )
add_test(test_user_full ./test_user_full)

add_executable(functional_gui_test ../HelloApp.cpp ../MainWindow.cpp ../User.cpp ../AskWindow.cpp ../SayWindow.cpp ../AdminWindow.cpp functional_gui_test.cpp)
TARGET_LINK_LIBRARIES(functional_gui_test ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}  ${wt} ${wtdbo} ${wttest} ${wtdbosqlite3} ${Boost_SIGNALS_LIBRARY})
add_test(functional_gui_test ./functional_gui_test)
