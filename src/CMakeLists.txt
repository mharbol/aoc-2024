add_executable(
    ${PROJECT_NAME}
    main.cpp
)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    cxx_setup
    tools_lib
    solution_lib
)
add_subdirectory(tools)
add_subdirectory(solution)
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}>
    "${CMAKE_BINARY_DIR}/bin"
)
