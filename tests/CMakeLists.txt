if (MINGW OR WIN32)
    add_executable(a_test windows_test.cpp)
else()
    add_executable(a_test linux_test.cpp)
endif()

add_test(NAME test1 COMMAND a_test)