project(Dvector)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(main src/main.cpp src/Dvector.cpp)
add_executable(test test/test.cpp src/Dvector.cpp)