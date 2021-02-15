# CMakeList.txt : CMake project for GameEngine2020, include source and define
# project specific logic here.
#

#ccmake[-Wno-dev]
# set minimum version required for CMake

function(message)
    if (NOT MESSAGE_QUIET)
        #_message(${ARGN})
    endif()
endfunction()

set(MESSAGE_QUIET OFF)

cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "GameEngine2020")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache


#if(CMAKE_SYSTEM_NAME EQUAL Windows)

#   else
#    set(SFML_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/lib/cmake/SFML")
#    set(SFML_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/lib")
#endif()

#set(SFML_DIR "${PROJECT_SOURCE_DIR}/libraries/SFML/lib/cmake/SFML")

set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")

#file(GLOB COMBINED_RESOURCE_FILES
#${RESOURCE_DIR}/animations/*
#${RESOURCE_DIR}/backgrounds/*
#${RESOURCE_DIR}/fonts/*
#${RESOURCE_DIR}/maps/*
#)

FILE(COPY ${RESOURCE_DIR} DESTINATION "${CMAKE_BINARY_DIR}")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(SOURCE_H "${PROJECT_SOURCE_DIR}/src/Header_Files")
set(SOURCE_C "${PROJECT_SOURCE_DIR}/src/Source_Files")

set(Actor_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Actor")
set(Actor_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Actor")

set(Behavior_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Behavior")
set(Behavior_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Behavior")

set(Graphics_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Graphics")
set(Graphics_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Graphics")

set(GUI_H "${PROJECT_SOURCE_DIR}/src/Header_Files/GUI")
set(GUI_C "${PROJECT_SOURCE_DIR}/src/Source_Files/GUI")

set(Level_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Level")
set(Level_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Level")

set(Physics_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Physics")
set(Physics_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Physics")

set(Bodies_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Physics/Bodies")
set(Bodies_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Physics/Bodies")

set(State_H "${PROJECT_SOURCE_DIR}/src/Header_Files/State")
set(State_C "${PROJECT_SOURCE_DIR}/src/Source_Files/State")

set(Util_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Util")
set(Util_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Util")

set(S2D_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Space2D")
set(S2D_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Space2D")

set(AS_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Behavior/ActionState")
set(AS_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Behavior/ActionState")

include_directories(
${SRC_DIR} ${Actor_H} ${Actor_C} ${Behavior_H} ${Behavior_C} ${Graphics_H} 
${Graphics_C} ${GUI_H} ${GUI_C} ${Level_H} ${Level_C} ${Physics_H} ${Physics_C} 
${State_H} ${State_C} ${Util_H} ${Util_C} ${S2D_H} ${S2D_C} ${Bodies_H} ${Bodies_C}
${AS_H} ${AS_C}
)

file(GLOB SRC
#"${Actor_H}/*.h"
#"${Actor_C}/*.cpp"
#"${Behavior_H}/*.h"
#"${Behavior_C}/*.cpp"
"${Graphics_H}/*.h"
"${Graphics_C}/*.cpp"
#"${GUI_H}/*.h"
#"${GUI_C}/*.cpp"
"${Level_H}/*.h"
"${Level_C}/*.cpp"
#"${Physics_H}/*.h"
#"${Physics_C}/*.cpp"
#"${State_H}/*.h"
#"${State_C}/*.cpp"
"${Util_H}/*.h"
"${Util_C}/*.cpp"
#"${S2D_H}/*.h"
#"${S2D_C}/*.cpp"
#"${Bodies_H}/*.h"
#"${Bodies_C}/*.cpp"
#"${AS_H}/*.h"
#"${AS_C}/*.cpp"
"${PROJECT_SOURCE_DIR}/src/Source_Files/GameEngine2020.cpp"
"${PROJECT_SOURCE_DIR}/src/Header_Files/GameEngine2020.h"
"${PROJECT_SOURCE_DIR}/src/Source_Files/include.cpp"
"${PROJECT_SOURCE_DIR}/src/Header_Files/include.h"
)

if(WIN32)

#windows-specific stuff
set(SFML_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/lib/cmake/SFML")

set(SFML_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/lib")
set(BOOST_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/boost_1_74_0/stage/lib")

set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/include")
set(BOOST_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/boost_1_74_0")
set(Boost_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/boost_1_74_0")

file(GLOB COMBINED_DLL_FILES "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/bin/*.dll")

#set(DLL_DIR )

FILE(COPY ${COMBINED_DLL_FILES} DESTINATION "${CMAKE_BINARY_DIR}")
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


    set(SFML_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/lib/cmake/SFML")

    set(SFML_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/lib")
    set(BOOST_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/boost_1_74_0/stage/lib")

    set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/include")
    set(BOOST_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/boost_1_74_0")
    set(Boost_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/boost_1_74_0")

    set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(MESSAGE_QUIET ON)
    message(STATUS "building on debug mode; debug_mode defined")
    set(MESSAGE_QUIET OFF)
    add_compile_definitions(debug_mode)
endif()


find_package(SFML 2.5 COMPONENTS graphics audio window network system REQUIRED)


   set(Boost_USE_STATIC_LIBS        ON)
   set(Boost_USE_MULTITHREADED      ON)
   set(Boost_USE_STATIC_RUNTIME    OFF)
   find_package(Boost 1.74.0 COMPONENTS date_time filesystem log system thread chrono atomic regex REQUIRED)

   include_directories(${Boost_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-audio sfml-system sfml-network)

#target_link_libraries(${PROJECT_NAME} ${BOOST_LIB_DIR})

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF)


target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#if(Boost_FOUND)
#   message(STATUS "boost found")
#endif()
#link_directories(${Boost_LOG_LIBRARY})
#include_directories(${Boost_INCLUDE_DIRS}) 
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} Boost::log)

#target_link_libraries(${PROJECT_NAME} 
#${SFML_LIB_DIR}/sfml-graphics-s-d
#${SFML_LIB_DIR}/sfml-window-s-d
#${SFML_LIB_DIR}/sfml-system-s-d
#${SFML_LIB_DIR}/opengl32
#${SFML_LIB_DIR}/freetype
#${SFML_LIB_DIR}/winmm
#${SFML_LIB_DIR}/gdi32
#${SFML_LIB_DIR}/sfml-audio-s-d
#${SFML_LIB_DIR}/openal32
#${SFML_LIB_DIR}/flac
#${SFML_LIB_DIR}/vorbisenc
#${SFML_LIB_DIR}/vorbisfile
#${SFML_LIB_DIR}/vorbis
#${SFML_LIB_DIR}/ogg
#${SFML_LIB_DIR}/sfml-network-s-d
#${SFML_LIB_DIR}/ws2_32
#)

#target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

include_directories(${SFML_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_H})

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

#add_subdirectory(${SRC_DIR})

#get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#foreach(dir ${dirs})
#  message(STATUS "dir='${dir}'")
#endforeach()
