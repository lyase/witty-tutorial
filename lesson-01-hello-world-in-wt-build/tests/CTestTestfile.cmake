# CMake generated Testfile for 
# Source directory: /home/ubsafder/temp/dojo/witty-tutorial/lesson-01-hello-world-in-wt/tests
# Build directory: /home/ubsafder/temp/dojo/witty-tutorial/lesson-01-hello-world-in-wt-build/tests
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(test_user_set_name "./test_user_set_name")
ADD_TEST(test_user_full "./test_user_full")
ADD_TEST(functional_tests_main_window_exists "./functional_test" "-i" "-s" "--detect_fp_exceptions=y" "--log-level=all" "--run_test=FunctionalSuite/testMainWindowExists")
ADD_TEST(test_ask_link "./functional_test" "-i" "-s" "--detect_fp_exceptions=y" "--log-level=all" "--run_test=FunctionalSuite/testAskLink")
ADD_TEST(test_user_persistence "./test_user_persistence" "-i" "-s" "--detect_fp_exceptions=y" "--log-level=all" "--run_test=testUserPersistenceSuite/testUserPersistence")
ADD_TEST(usertest "./usertest")
ADD_TEST(dbo_functions_test "./dbo_test" "-i" "-s" "--detect_fp_exceptions=y" "--log-level=all" "--")
ADD_TEST(phptest "phpunit" "/home/ubsafder/temp/dojo/witty-tutorial/lesson-01-hello-world-in-wt-build/tests/testPass.php")
ADD_TEST(pytest "/home/ubsafder/temp/dojo/witty-tutorial/lesson-01-hello-world-in-wt-build/tests/testPass.py")
