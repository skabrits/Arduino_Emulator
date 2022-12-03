# Arduino_Emulator
C++ emulator for Arduino
## Setup
В файле [CMakeLists.txt] нужно в зависимости
от os на которой билдится из 2-х строчек 
выбрать правильную:
```
add_executable(Arduino_Emulator main_windows.cpp)

# For linux OS uncomment following line and comment line above

#add_executable(Arduino_Emulator main_linux.cpp)

# For testing pieces of code uncomment following line and comment lines above

#add_executable(Arduino_Emulator test.cpp) 
# This allows to run instead of file main_windows.cpp 
# run file test.cpp, usefull to test small features
```
Это связано с тем, что stepik не поддерживает многопоточность, но код там
выполняется в среде Linux ?alpine?, а на винде, та команда которую я нашёл
для проверки наличия бит в stdin не работает.
Поэтому пока что версия для винды работает с многопоточностью,
а версия для линукса не работает на винде.
