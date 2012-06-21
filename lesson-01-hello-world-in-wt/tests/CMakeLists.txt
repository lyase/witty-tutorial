project(tests)

#add_executable(test_user_is_not_mike ../testUser_Class_dbo.cpp test_user_is_not_mike.cpp)
add_executable(test_user_is_not_mike ../testUser_Class_dbo.cpp) 
TARGET_LINK_LIBRARIES(test_user_is_not_mike ${wt} ${wdbo} ${wtdbosqlite3}  )
add_test(test_user_is_not_mike test_user_is_not_mike)
