# CMakeList.txt : CMake project for GameEngine2020, include source and define
# project specific logic here.
#


#ccmake[-Wno-dev]
# set minimum version required for CMake

cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "GameEngine2020")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RESOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")

#file(GLOB COMBINED_RESOURCE_FILES
#${RESOURCE_DIR}/animations/*
#${RESOURCE_DIR}/backgrounds/*
#${RESOURCE_DIR}/fonts/*
#${RESOURCE_DIR}/maps/*
#)

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
"${Graphics_C}/*.cpp"
#"${GUI_C}/*.cpp"
"${Level_C}/*.cpp"
#"${Physics_C}/*.cpp"
#"${State_C}/*.cpp"
"${Util_C}/*.cpp"
#"${S2D_C}/*.cpp"
#"${Bodies_C}/*.cpp"
#"${AS_C}/*.cpp" 
"${Component_C}/*.cpp"
"${MAP_C}/*.cpp"
"${SOURCE_C}/*.cpp"
#"${PROJECT_SOURCE_DIR}/src/Source_Files/GameEngine2020.cpp"
#"${PROJECT_SOURCE_DIR}/src/Source_Files/include.cpp"
)



#set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

#MACRO(HEADER_DIRECTORIES return_list)
#    FILE(GLOB_RECURSE new_list ${SRC_DIR}/*.h)
#    SET(dir_list "")
#    FOREACH(file_path ${new_list})
#        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
#        SET(dir_list ${dir_list} ${dir_path})
#    ENDFOREACH()
#    LIST(REMOVE_DUPLICATES dir_list)
#    SET(${return_list} ${dir_list})
#ENDMACRO()

#file(GLOB_RECURSE SRC ${SRC_DIR}/*.cpp)

if(WIN32)

#windows-specific stuff
#set(SFML_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/lib/cmake/SFML")

#set(SFML_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/lib")
#set(BOOST_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/boost_1_74_0/stage/lib")

#set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/include")
#set(BOOST_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/boost_1_74_0")
#set(Boost_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Windows/boost_1_74_0")
#set(NLOHMANN "${PROJECT_SOURCE_DIR}/libraries/Windows/nlohmann")
#set(TILESON "${PROJECT_SOURCE_DIR}/libraries/Windows/tileson")

#file(GLOB COMBINED_DLL_FILES "${PROJECT_SOURCE_DIR}/libraries/Windows/SFML/bin/*.dll")


#FILE(COPY ${COMBINED_DLL_FILES} DESTINATION "${CMAKE_BINARY_DIR}")
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


  #set(SFML_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/lib/cmake/SFML")

  #set(SFML_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/lib")
  #set(BOOST_LIB_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/boost_1_74_0/stage/lib")

  #set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/SFML/include")
  #set(BOOST_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/boost_1_74_0")
  #set(Boost_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libraries/Linux/boost_1_74_0")
  #set(NLOHMANN "${PROJECT_SOURCE_DIR}/libraries/Linux/nlohmann")
  #set(TILESON "${PROJECT_SOURCE_DIR}/libraries/Linux/tileson")

  set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(MESSAGE_QUIET ON)
    message(STATUS "building on debug mode; debug_mode defined")
    set(MESSAGE_QUIET OFF)
    add_compile_definitions(debug_mode)
endif()

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Boost REQUIRED)
#find_package(TMXLITE REQUIRED)



set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

include_directories(${SFML_INCLUDE_DIR})
#include_directories(${TMXLITE_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})



add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} PUBLIC ${TMXLITE_LIBRARIES})

#target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-audio sfml-system sfml-network)



#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


#include_directories(${SFML_INCLUDE_DIR})
#include_directories(${BOOST_INCLUDE_DIR})
#target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
#target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_INCLUDE_DIR})
#target_include_directories(${PROJECT_NAME} PUBLIC ${NLOHMANN})
#target_include_directories(${PROJECT_NAME} PUBLIC ${TILESON})
#target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_H})


#HEADER_DIRECTORIES(header_dir_list)

#list(LENGTH header_dir_list header_dir_list_count)
#message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")

#target_include_directories(
#    ${PROJECT_NAME}
#    PUBLIC
#    ${header_dir_list} # Recursive
#)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
