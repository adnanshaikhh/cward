cmake_minimum_required(VERSION 3.6)
project(cward)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # Replace warning level from the default /W3  to /W4
  # string (REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
  # string (REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  # MESSAGE( "Compiling with options: ${CMAKE_CXX_FLAGS}")
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
  MESSAGE( "Compiling with options: ${CMAKE_CXX_FLAGS}")
endif()

if (WIN32)
  set(SDL_DIR "$ENV{USERPROFILE}/work/libs/SDL2-2.0.7")
  set(GLEW_DIR "$ENV{USERPROFILE}/work/libs/glew-2.1.0")
  set(WIN_KIT_LIB "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um")
else ()
  find_package(SDL2 REQUIRED)
endif ()

include_directories(${SDL_DIR}/include ${GLEW_DIR}/include include)

set(SOURCE_FILES src/main.c src/log.c src/graphics.c src/timer.c src/mathops.c)

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  MESSAGE("Using 64-bit libraries")
  set(SDL2_LIBRARIES "${SDL_DIR}/lib/x64/SDL2.lib;${SDL_DIR}/lib/x64/SDL2main.lib")
  set(GLEW_LIBRARIES "${GLEW_DIR}/lib/Release/x64/glew32.lib;${GLEW_DIR}/lib/Release/x64/glew32s.lib")
  set(OPENGL_LIBRARY "${WIN_KIT_LIB}/x64/OpenGL32.lib")
else ()
  MESSAGE("Using 32-bit libraries")
  set(SDL2_LIBRARIES "${SDL_DIR}/lib/x86/SDL2.lib;${SDL_DIR}/lib/x86/SDL2main.lib")
  set(GLEW_LIBRARIES "${GLEW_DIR}/lib/Release/Win32/glew32.lib;${GLEW_DIR}/lib/Release/Win32/glew32s.lib")
  set(OPENGL_LIBRARY "${WIN_KIT_LIB}/x86/OpenGL32.lib")
endif ()

add_executable(cward ${SOURCE_FILES})
target_link_libraries(cward ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARY})

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "cward" )

