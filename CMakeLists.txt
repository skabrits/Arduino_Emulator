cmake_minimum_required(VERSION 3.24)
project(Arduino_Emulator)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Is Unix ${UNIX}")
message(STATUS "Is MINGW ${MINGW}")
message(STATUS "Is VS code ${MSVC}")
message(STATUS "Is Windows ${WIN32}")
message(STATUS "Is OS X ${APPLE}")
if (MINGW OR WIN32)
    find_package( Threads )
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")

    add_executable(Arduino_Emulator main_windows.cpp)

    target_link_libraries( Arduino_Emulator ${CMAKE_THREAD_LIBS_INIT} )
else()
    add_executable(Arduino_Emulator main_linux.cpp)
endif ()

enable_testing()

add_subdirectory(tests)



# For testing small pieces of code uncomment following line and comment lines above

#add_executable(Arduino_Emulator test.cpp)
