set(GLAD_SOURCES glad/src/glad.c)
set(GLAD_INCLUDE_DIR glad/include)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE

# if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
# 	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
# 	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
# elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
#   # Replace warning level from the default /W3  to /W4
#   # string (REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
#   # string (REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#   # MESSAGE( "Compiling with options: ${CMAKE_CXX_FLAGS}")
#     # Force to always compile with W4
#     if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
#     string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#   else()
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#   endif()
#   MESSAGE( "Compiling with options: ${CMAKE_CXX_FLAGS}")
# endif()

# if (WIN32)
#   set(SDL_DIR "$ENV{USERPROFILE}/work/libs/SDL2-2.0.7")
#   set(GLEW_DIR "$ENV{USERPROFILE}/work/libs/glew-2.1.0")
#   set(WIN_KIT_LIB "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um")
# else ()
#   find_package(SDL2 REQUIRED)
# endif ()


set(CWARD_SOURCES
    main.cc
    game.cc
    mathops.cc
    ${GLAD_SOURCES}
    )

# Support both 32 and 64 bit builds

# if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
# MESSAGE("Using 64-bit libraries")
# set(SDL2_LIBRARIES "${SDL_DIR}/lib/x64/SDL2.lib;${SDL_DIR}/lib/x64/SDL2main.lib")
# set(GLEW_LIBRARIES "${GLEW_DIR}/lib/Release/x64/glew32.lib;${GLEW_DIR}/lib/Release/x64/glew32s.lib")
# set(OPENGL_LIBRARY "${WIN_KIT_LIB}/x64/OpenGL32.lib")
# else ()
# MESSAGE("Using 32-bit libraries")
# set(SDL2_LIBRARIES "${SDL_DIR}/lib/x86/SDL2.lib;${SDL_DIR}/lib/x86/SDL2main.lib")
# set(GLEW_LIBRARIES "${GLEW_DIR}/lib/Release/Win32/glew32.lib;${GLEW_DIR}/lib/Release/Win32/glew32s.lib")
# set(OPENGL_LIBRARY "${WIN_KIT_LIB}/x86/OpenGL32.lib")
# endif ()

add_executable(cward ${CWARD_SOURCES})
target_link_libraries(cward glfw tinyobjloader)
target_include_directories(cward PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(cward PUBLIC ../third_party/tinyobjloader)
target_include_directories(cward PUBLIC ../third_party/glm)
target_include_directories(cward PUBLIC ${GLAD_INCLUDE_DIR})

# Copy over asset directories on modification.
add_custom_command(TARGET cward POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/model
                   ${CMAKE_BINARY_DIR}/model)
add_custom_command(TARGET cward POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/tex
                   ${CMAKE_BINARY_DIR}/tex)

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "cward" )

