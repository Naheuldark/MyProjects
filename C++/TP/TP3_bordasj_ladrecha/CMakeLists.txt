project(Height)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(main src/main.cpp src/Dvector.cpp src/Height.cpp src/WaveModel.cpp src/GerstnerWave.cpp src/GerstnerWaveModel.cpp)
add_executable(test test/test.cpp src/Dvector.cpp src/Height.cpp src/WaveModel.cpp src/GerstnerWave.cpp src/GerstnerWaveModel.cpp)
