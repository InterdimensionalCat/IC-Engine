# CMakeList.txt : CMake project for GameEngine2020, include source and define
# project specific logic here.
#


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

set(SOURCE_H "${PROJECT_SOURCE_DIR}/src/Header_Files")
set(SOURCE_C "${PROJECT_SOURCE_DIR}/src/Source_Files")

set(Actor_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Actor")
set(Actor_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Actor")

set(Audio_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Audio")
set(Audio_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Audio")

set(Ai_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Ai")
set(Ai_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Ai")

set(Level_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Level")
set(Level_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Level")

set(Graphics_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Graphics")
set(Graphics_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Graphics")

set(Tmap_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Tilemap")
set(Tmap_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Tilemap")

set(Comp_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Component")
set(Comp_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Component")

set(Util_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Util")
set(Util_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Util")

set(Scene_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Scene")
set(Scene_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Scene")

set(Wind_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Window")
set(Wind_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Window")

set(Sys_H "${PROJECT_SOURCE_DIR}/src/Header_Files/System")
set(Sys_C "${PROJECT_SOURCE_DIR}/src/Source_Files/System")

include_directories(
${SRC_DIR} ${SOURCE_H} ${Graphics_H} ${Util_H} 
${Comp_H} ${Scene_H} ${Wind_H} ${Audio_H} 
${Ai_H} ${Tmap_H} ${Sys_H} ${Actor_H} ${Level_H}
)

file(GLOB SRC
"${Actor_C}/*.cpp"
"${Actor_H}/*.h"
"${Audio_C}/*.cpp"
"${Audio_H}/*.h"
"${Ai_C}/*.cpp"
"${Ai_H}/*.h"
"${Level_C}/*.cpp"
"${Level_H}/*.h"
"${Tmap_H}/*.h"
"${Tmap_C}/*.cpp"
"${Graphics_C}/*.cpp"
"${Graphics_H}/*.h"
"${Util_C}/*.cpp"
"${Util_H}/*.h"
"${Scene_C}/*.cpp"
"${Scene_H}/*.h"
"${Sys_H}/*.h"
"${Sys_C}/*.cpp"
"${Wind_H}/*.h"
"${Wind_C}/*.cpp"
"${Comp_H}/*.h"
"${Comp_C}/*.cpp"
"${SOURCE_C}/*.cpp"
"${SOURCE_H}/*.h"
)


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

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
#set(${CMAKE_MODULE_PATH} APPEND Findtmxlite.cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(tmxlite REQUIRED)
#find_package(Space2D REQUIRED)
find_package(spdlog REQUIRED)


cmake_path(SET TMXLITE_INCLUDE NORMALIZE "${TMXLITE_INCLUDE_DIR}/../")
cmake_path(SET SPDLOG_INCLUDE_DIR NORMALIZE "${spdlog_DIR}/include/")

include_directories(${TMXLITE_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
#include_directories(${Space2D_INCLUDE_DIR})
include_directories(${SPDLOG_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)

target_link_libraries(${PROJECT_NAME} PRIVATE ${spdlog_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} PRIVATE Space2D)

if(CMAKE_BUILD_TYPE MATCHES Debug)
file(GLOB SFML_DLL ${SFML_DIR}/lib/Debug/*.dll)
cmake_path(SET TMXLITE_DLL NORMALIZE "${TMXLITE_LIBRARIES}/tmxlite-d.dll")
cmake_path(SET TMXLITE_LIB NORMALIZE "${TMXLITE_LIBRARIES}/tmxlite-d.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE ${TMXLITE_LIB})
FILE(COPY ${SFML_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY ${TMXLITE_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
else()
file(GLOB SFML_DLL ${SFML_DIR}/lib/Release/*.dll)
cmake_path(SET TMXLITE_DLL NORMALIZE "${TMXLITE_LIBRARIES}/tmxlite.dll")
cmake_path(SET TMXLITE_LIB NORMALIZE "${TMXLITE_LIBRARIES}/tmxlite.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE ${TMXLITE_LIB})
FILE(COPY ${SFML_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
FILE(COPY ${TMXLITE_DLL} DESTINATION "${CMAKE_BINARY_DIR}")
endif()


target_precompile_headers(${PROJECT_NAME} PUBLIC [["include.h"]])

if(MSVC) 
foreach(source IN LISTS SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE ${PROJECT_SOURCE_DIR}/src/ "" source_rel ${source_path})
    string(REPLACE "/" "\\" source_path_msvc "${source_rel}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
endif()


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
