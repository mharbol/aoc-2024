
add_library(
    solution_lib
    Solution.cpp 
    Day00.cpp
)

target_link_libraries(solution_lib PRIVATE cxx_setup)
