file(GLOB CPP_SOURCE_FILES "*.cpp" "*.hpp" "*.c" "*.h")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(src ${CPP_SOURCE_FILES})


target_include_directories(src PRIVATE ${CMAKE_CURRENT_LIST_DIR})
