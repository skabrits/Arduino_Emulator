cmake_minimum_required(VERSION 3.24)
project(Arduino_Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arduino_Emulator main_windows.cpp)

# For linux OS uncomment following line and comment line above

#add_executable(Arduino_Emulator main_linux.cpp)

# For testing pieces of code uncomment following line and comment lines above

#add_executable(Arduino_Emulator test.cpp)