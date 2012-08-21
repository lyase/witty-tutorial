project(tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing

CONFIGURE_FILE(wt-config.xml wt-config.xml)

find_library(wttest wttest)

add_executable(test_user_set_name ../User.cpp test_user_is_not_mike.cpp)
find_package(Boost COMPONENTS system filesystem REQUIRED)
TARGET_LINK_LIBRARIES(test_user_set_name 
                     ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY}
                     ${hpdf}
                     ${wt} ${wtdbo} ${wtdbosqlite3} )
add_test( test_user_set_name ./test_user_set_name )

add_executable(test_user_full ../User.cpp ../testUser_Class_dbo.cpp ../listing.cpp)
TARGET_LINK_LIBRARIES(test_user_full 
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY}
                      ${hpdf}
                      ${wt} ${wtdbo} ${wtdbosqlite3} )
add_test(test_user_full ./test_user_full)

ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN ) # So tests load the test lib dynamically

add_executable(functional_test ../HelloApp.cpp ../MainWindow.cpp ../User.cpp ../AskWindow.cpp ../SayWindow.cpp ../AdminWindow.cpp functional_test.cpp)
TARGET_LINK_LIBRARIES(functional_test
    ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${hpdf}
    ${wt} ${wtdbo} ${wttest} ${wtdbosqlite3} )
add_test(test_main_window_exists ./functional_test -i -s --detect_fp_exceptions=y --log-level=all --run_test=FunctionalSuite/testMainWindowExists)
add_test(test_ask_link ./functional_test -i -s --detect_fp_exceptions=y --log-level=all --run_test=FunctionalSuite/testAskLink)

add_executable(usertest ../User.cpp ../testUser_Class.cpp )
TARGET_LINK_LIBRARIES(usertest 
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${hpdf}
                      ${wt} ${wtdbo} ${wtdbosqlite3} )
add_test(usertest ./usertest)
add_executable(dbo_test testdbo.cpp )
TARGET_LINK_LIBRARIES(dbo_test
    ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_SIGNALS_LIBRARY}
    ${hpdf}
    ${wt} ${wtdbo} ${wttest} ${wtdbosqlite3} )
add_test(dbo_functions_test ./dbo_test -i -s --detect_fp_exceptions=y --log-level=all --)
file(COPY testPass.php DESTINATION .)
add_test(phptest phpunit ${CMAKE_CURRENT_BINARY_DIR}/testPass.php)

file(COPY testPass.py DESTINATION .)
add_test(pytest ${CMAKE_CURRENT_BINARY_DIR}/testPass.py)

add_executable(test_user_persistence ../HelloApp.cpp ../User.cpp testUserPersistence.cpp)
TARGET_LINK_LIBRARIES(usertest 
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${hpdf}
                      ${wt} ${wthttp} ${wtdbo} ${wtdbosqlite3} )


