
add_library(
    util_lib
    ArgParse.cpp
    fileread.cpp
)
target_link_libraries(
    util_lib PRIVATE
    cxx_setup
)
