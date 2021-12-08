# CMakeList.txt : CMake project for GameEngine2020, include source and define
# project specific logic here.
#

#macro that recursively finds header files
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

#ccmake[-Wno-dev]
# set minimum version required for CMake

cmake_minimum_required (VERSION 3.20)

#SET(SFML_DLL_DIR "not found" CACHE STRING)

set(PROJECT_NAME "GameEngine2020")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")


#adds resource files to the build
FILE(COPY ${RESOURCE_DIR} DESTINATION "${CMAKE_BINARY_DIR}")



set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
FILE(GLOB_RECURSE CPP_FILES ${SRC_DIR}/*.cpp)

Message("Cpp dir: ${CPP_FILES}")
HEADER_DIRECTORIES(header_dir_list)

list(LENGTH header_dir_list header_dir_list_count)
message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")

include_directories(PUBLIC ${header_dir_list})



if(WIN32)

#windows-specific stuff

else()

  #linux-specific stuff
  set(MESSAGE_QUIET ON)
  MESSAGE("Searching X11")
  set(MESSAGE_QUIET OFF)
  FIND_PACKAGE(X11 REQUIRED)
  IF(X11_FOUND)
    set(MESSAGE_QUIET ON)
    MESSAGE(" X11 include path: " ${X11_INCLUDE_DIR})
    MESSAGE(" X11 library path: " ${X11_LIBRARIES})
    set(MESSAGE_QUIET OFF)
  ENDIF(X11_FOUND)

  set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(MESSAGE_QUIET ON)
    message(STATUS "building on debug mode; debug_mode defined")
    set(MESSAGE_QUIET OFF)
    add_compile_definitions(debug_mode)
endif()


set(SFML_STATIC_LIBRARIES FALSE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    FILE(GLOB EXT_LIBS ${PROJECT_SOURCE_DIR}/Dependancies/lib/Debug/*.lib)
    FILE(GLOB EXT_DLL  ${PROJECT_SOURCE_DIR}/Dependancies/bin/Debug/*.dll)
    FILE(COPY ${EXT_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
else()
    FILE(GLOB EXT_LIBS ${PROJECT_SOURCE_DIR}/Dependancies/lib/Release/*.lib)
    FILE(GLOB EXT_DLL  ${PROJECT_SOURCE_DIR}/Dependancies/bin/Release/*.dll)
    FILE(COPY ${EXT_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
endif()

find_package(OpenGL REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/Dependancies/include")

include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXT_LIBS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})


target_precompile_headers(${PROJECT_NAME} PUBLIC [["include.h"]])


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
