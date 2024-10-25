project(GameboyEmulator)
cmake_minimum_required(VERSION 3.25)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(tests)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} mylib)
