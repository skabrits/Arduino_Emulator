# Arduino_Emulator
C++ emulator for Arduino
## Setup
В файле [CMakeLists.txt](./CMakeLists.txt) в зависимость от системы 
автоматически выбирается либо multithread version либо версия без потоков:
```
if (MINGW OR WIN32)
    find_package( Threads )
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")

    add_executable(Arduino_Emulator main_windows.cpp)

    target_link_libraries( Arduino_Emulator ${CMAKE_THREAD_LIBS_INIT} )
else()
    add_executable(Arduino_Emulator main_linux.cpp)
endif ()
```
Это связано с тем, что stepik не поддерживает многопоточность, но код там
выполняется в среде Linux ?alpine?, а на винде, та команда которую я нашёл
для проверки наличия бит в stdin не работает.
Поэтому пока что версия для винды работает с многопоточностью,
а версия для линукса не работает на винде.
## Branching
main branch is protected, поэтому пушить туда напрямую не получится. 
При имплементации той или иной фичи нужно делать
```
git checkout -b feature_name_branch
```
и имплементировав новую фичу пушить всё [в эту бренчу](https://stackoverflow.com/questions/5697750/what-exactly-does-the-u-do-git-push-u-origin-master-vs-git-push-origin-ma):
```
git push -u origin feature_name_branch
```
После этого делается pull request на merge feature_name_branch
и main [в интерфейсе](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request) гитхаба.
После этого можно удалить ветку в гитхабе (через интерфейс)
и [локально](https://dillionmegida.com/p/delete-outdated-branches/#:~:text=look%20at%20them.-,git%20remote%20prune%20origin,branch%2Dafter%20merge%2Doperation.):
```
git fetch --prune
```
