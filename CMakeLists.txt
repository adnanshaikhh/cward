cmake_minimum_required(VERSION 2.6)
project(cward)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (WIN32)
  set (ENV{SDLDIR} "D:/work/libraries/windows/SDL2-2.0.5")
  set(SDL2_INCLUDE_DIR "D:/work/libraries/windows/SDL2-2.0.5/include")
  set(SDL2_LIBRARY "D:/work/libraries/windows/SDL2-2.0.5/lib/x86/SDL2.lib")
  set(GLEW_INCLUDE_DIR "D:/work/libraries/windows/glew-2.0.0/include/")
  set(GLEW_LIBRARY1 "D:/work/libraries/windows/glew-2.0.0/lib/Release/Win32/glew32.lib")
  set(GLEW_LIBRARY2 "D:/work/libraries/windows/glew-2.0.0/lib/Release/Win32/glew32s.lib")
  set(OPENGL_LIBRARY "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.14393.0/um/x86/OpenGL32.lib")
else ()
  find_package(SDL2 REQUIRED)
endif ()

include_directories(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

set(SOURCE_FILES src/main.c)

add_executable(cward ${SOURCE_FILES})
target_link_libraries(cward ${SDL2_LIBRARY} ${GLEW_LIBRARY1} ${GLEW_LIBRARY2} ${OPENGL_LIBRARY})
