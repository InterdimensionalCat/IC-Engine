# CMakeList.txt : CMake project for GameEngine2020, include source and define
# project specific logic here.
#


#ccmake[-Wno-dev]
# set minimum version required for CMake

cmake_minimum_required (VERSION 3.16)

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

set(Component_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Component")
set(Component_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Component")

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

set(MAP_H "${PROJECT_SOURCE_DIR}/src/Header_Files/Map")
set(MAP_C "${PROJECT_SOURCE_DIR}/src/Source_Files/Map")

include_directories(
${SRC_DIR} ${SOURCE_H} ${Actor_H} ${Behavior_H} ${Graphics_H} 
${GUI_H} ${Level_H} ${Physics_H} ${State_H} ${Util_H} 
${S2D_H} ${Bodies_H} ${AS_H} ${Component_H} ${MAP_H}
)

file(GLOB SRC
#"${Actor_C}/*.cpp"
#"${Behavior_C}/*.cpp"
#"${Graphics_C}/*.cpp"
#"${Graphics_H}/*.h"
#"${GUI_C}/*.cpp"
#"${Level_C}/*.cpp"
#"${Level_H}/*.h"
#"${Physics_C}/*.cpp"
#"${State_C}/*.cpp"
"${Util_C}/*.cpp"
"${Util_H}/*.h"
#"${S2D_C}/*.cpp"
#"${Bodies_C}/*.cpp"
#"${AS_C}/*.cpp" 
#"${Component_C}/*.cpp"
#"${Component_H}/*.h"
#"${MAP_C}/*.cpp"
#"${MAP_H}/*.h"
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

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)



include_directories(${SFML_INCLUDE_DIR})


add_executable(${PROJECT_NAME} ${SRC})


target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)


target_precompile_headers(${PROJECT_NAME} PUBLIC [["include.h"]])

if(MSVC) 
foreach(source IN LISTS SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE ${PROJECT_SOURCE_DIR}/src/ "" source_rel ${source_path})
    message(${source_rel})
    string(REPLACE "/" "\\" source_path_msvc "${source_rel}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()
endif()


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
