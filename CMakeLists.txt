PROJECT(LearningWittystepbystep)
cmake_minimum_required(VERSION 2.8)
add_subdirectory(lesson-00-hello-world-in-cpp)
add_subdirectory(lesson-01-hello-world-in-wt)
add_subdirectory(lesson-02-events)
add_subdirectory(lesson-03-static-content)
add_subdirectory(lesson-04-links)
add_subdirectory(lesson-05-auth)
add_subdirectory(lesson-06-auth2)
add_subdirectory(lesson-07-rest-api)
# Tests
enable_testing()
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generatedStatic"
    COMMAND doxygen doxy.config
    COMMAND mkdir ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic
    COMMAND mv doc ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic/
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_custom_target(topleveldoc DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generatedStatic)
