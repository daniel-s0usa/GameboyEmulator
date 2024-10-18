project(GameboyEmulator)
cmake_minimum_required(VERSION 3.25)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(tests)


# Notes 
#find_package (Threads REQUIRED) #find pthreads package
#target_link_libraries (my_exe my_lib ${CMAKE_THREAD_LIBS_INIT}) #link against pthreads and my_lib

