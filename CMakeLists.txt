cmake_minimum_required(VERSION 2.6)
project(cward)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (WIN32)
  #{SDL_DIR}
  #{GLEW_DIR}
else ()
  find_package(SDL2 REQUIRED)
endif ()

include_directories($ENV{SDL_DIR}/include $ENV{GLEW_DIR}/include include)

set(SOURCE_FILES src/main.c src/log.c src/graphics.c)

add_executable(cward ${SOURCE_FILES})
target_link_libraries(cward $ENV{SDL_DIR}/lib/x64/SDL2.lib $ENV{SDL_DIR}/lib/x64/SDL2main.lib $ENV{GLEW_DIR}/lib/Release/x64/glew32.lib $ENV{GLEW_DIR}/lib/Release/x64/glew32s.lib $ENV{LIBRARY}/x64/OpenGL32.lib)
