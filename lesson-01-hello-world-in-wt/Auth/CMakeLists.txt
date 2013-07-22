project(Auth)

add_library(Auth STATIC Services.cpp Session.cpp)
target_link_libraries(Auth models)
