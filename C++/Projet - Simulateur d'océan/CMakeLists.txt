project(Dvector)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(main src/main.cpp src/Dvector.cpp src/GenericVector.h src/GerstnerWave.cpp src/GerstnerWaveModel.cpp src/Height.cpp src/Ocean.cpp src/WaveModel.cpp)

add_executable(philips src/philips.cpp src/Dvector.cpp src/GenericVector.h src/PhilipsWaveModel.cpp src/Height.cpp src/Ocean.cpp src/WaveModel.cpp src/fft.cpp)

add_executable(test test/test.cpp src/Dvector.cpp src/GenericVector.h src/GerstnerWave.cpp src/GerstnerWaveModel.cpp src/Height.cpp src/Ocean.cpp src/WaveModel.cpp)
