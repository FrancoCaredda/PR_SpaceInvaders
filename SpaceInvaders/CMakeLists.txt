cmake_minimum_required(VERSION 3.8)

project("SpaceInvaders")

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} "src/main.cpp" 
"src/Game.h" 
"src/Game.cpp" 
"src/GameObjects/Spaceship.h" 
"src/GameObjects/Spaceship.cpp" 
"src/Core/Spritesheet.h" 
"src/Core/Spritesheet.cpp"  
"src/Core/Object.h" 
"src/Core/Renderer.h" 
"src/Core/Renderer.cpp" 
"src/Core/Object.cpp" 
"src/Core/Components.h" 
"src/GameObjects/GameObjectPool.h"
"src/GameObjects/GameObjectPool.cpp"
"src/GameObjects/Projectile.h" 
"src/GameObjects/Alien.h"
"src/GameObjects/Alien.cpp" "src/Core/Physics.h" "src/Core/Physics.cpp")
add_compile_definitions(RESOURCE_DIR="${CMAKE_SOURCE_DIR}/assets")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include"
												  "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/lib")
target_link_libraries(${PROJECT_NAME} PUBLIC "raylib.lib"
											 "winmm.lib")