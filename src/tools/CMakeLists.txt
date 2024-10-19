
add_library(
    tools_lib
    ArgParse.cpp
    fileread.cpp
)
target_link_libraries(
    tools_lib PRIVATE
    cxx_setup
)
