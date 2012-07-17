project(tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing

CONFIGURE_FILE(wt-config.xml wt-config.xml)

find_library(wttest wttest)

add_executable(test_user_set_name ../User.cpp test_user_is_not_mike.cpp)
find_package(Boost COMPONENTS system filesystem REQUIRED)

TARGET_LINK_LIBRARIES(test_user_set_name )
add_test( test_user_set_name ./test_user_set_name )

add_executable(test_user_full ../User.cpp ../testUser_Class_dbo.cpp ../listing.cpp)
TARGET_LINK_LIBRARIES(test_user_full ${wt} ${wtdbo} ${wtdbosqlite3} ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} )
add_test(test_user_full ./test_user_full)

ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN ) # So tests load the test lib dynamically

add_executable(functional_gui_test ../HelloApp.cpp ../MainWindow.cpp ../User.cpp ../AskWindow.cpp ../SayWindow.cpp ../AdminWindow.cpp functional_gui_test.cpp)
TARGET_LINK_LIBRARIES(functional_gui_test ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${wt} ${wtdbo} ${wttest} ${wtdbosqlite3} )
add_test(test_main_window_exists ./functional_gui_test -i -s --detect_fp_exceptions=y --log-level=all --run_test=FunctionalGuiSuite/testMainWindowExists)
add_test(test_ask_link ./functional_gui_test -i -s --detect_fp_exceptions=y --log-level=all --run_test=FunctionalGuiSuite/testAskLink)

add_executable(usertest ../User.cpp ../testUser_Class.cpp )
    TARGET_LINK_LIBRARIES(usertest ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}  )
add_test(usertest ./usertest)
add_executable(dbo_test testdbo.cpp )
TARGET_LINK_LIBRARIES(dbo_test ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${wt} ${wtdbo} ${wttest} ${wtdbosqlite3} )
add_test(dbo_functions_test ./dbo_test -i -s --detect_fp_exceptions=y --log-level=all --)
add_test(phptest phpunit /home/desafder/witty-tutorial/lesson-01-hello-world-in-wt/tests/test1.php)

file(COPY testPass.py DESTINATION .)
add_test(pytest ${CMAKE_CURRENT_BINARY_DIR}/testPass.py)
