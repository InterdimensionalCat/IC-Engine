# CMakeList.txt : CMake project for GameEngine2020, include source and define
# project specific logic here.
#
# set minimum version required for CMake
cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "GameEngine2020")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(${PROJECT_NAME})

## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "${CMAKE_CURRENT_LIST_DR}/SFML/lib/cmake/SFML")

#file(GLOB ALL_REQUIRED_DLL "${CMAKE_CURRENT_LIST_DR}/SFML/bin/*.dll")
#file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES 
ActionState.h 
ActionStateMap.cpp 
ActionStateMap.h
Actor.cpp
Actor.h
Animation.cpp
Animation.h
Behavior.cpp
Behavoir.h
Button.cpp
Button.h
Camera.cpp
Camera.h
CollisionEvent.cpp
CollisionEvent.h
ColPair.cpp
ColPair.h
Composite.cpp
Composite.h
Driver.cpp
Driver.h
GameEngine2020.cpp
GameEngine2020.h
GameTransform.cpp
GameTransform.h
include.cpp
include.h
InputHandle.cpp
InputHandle.h
Level.cpp
Level.h
MapEditorState.cpp
MapEditorState.h
MenuState.cpp
MenuState.h
OneWayBody.cpp
OneWayBody.h
PhysicsBody.cpp
PhysicsBody.h
PhysicsEngine.cpp
PhysicsEngine.h
PhysMath.cpp
PhysMath.h
Player.cpp
Player.h
PlayerAirborneState.cpp
PlayerAirborneState.h
PlayerIdleState.cpp
PlayerIdleState.h
PlayerJumpState.cpp
PlayerJumpState.h
PlayerMoveState.cpp
PlayerMoveState.h
PlayerRunState.cpp
PlayerRunState.h
PolygonBody.cpp
PolygonBody.h
Renderer.cpp
Renderer.h
RigidBody.cpp
RigidBody.h
State.cpp
State.h
StateManager.cpp
StateManager.h
StaticBody.cpp
StaticBody.h
SweepAndPrune.cpp
SweepAndPrune.h
TestActor.h
Tile.cpp
Tile.h
TileButton.cpp
TileButton.h
TileDriver.cpp
TileDriver.h
TileEditor.cpp
TileEditor.h
TileMap.cpp
TileMap.h
TileSet.cpp
TileSet.h
)

find_package(SFML 2.5 COMPONENTS graphics audio main network system window REQUIRED)
add_executable(${PROJECT_NAME} GameEngine2020.cpp GameEngine2020.h)
target_link_libraries(${PROJECT_NAME} sfml-graphics-d sfml-audio-d sfml-system-d sfml-window-d)
