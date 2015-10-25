cmake_minimum_required (VERSION 3.0.0)
project (Ballsy)

option(WANT_ANDROID "Build for Android" OFF)

set(GAME_FILE_DIRECTORY "Ballsy")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wno-unused-parameter") 
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(GAME_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE GAME_CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${GAME_SOURCE_DIRECTORY}/*.cpp")
file(GLOB_RECURSE GAME_ALL_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${GAME_SOURCE_DIRECTORY}/*")

message(STATUS "CPP: ${GAME_CPP_SOURCES}")
message(STATUS "ALL: ${GAME_ALL_SOURCES}")

if(WANT_ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANDROID=1") 
    set(ANDROID_TARGET "android-15" CACHE STRING "What Android target to compile for.")
    include(${CMAKE_SOURCE_DIR}/cmake/Android.cmake)
else()
    file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets/)

    find_package(Allegro5 REQUIRED)

    include_directories(${ALLEGRO_INCLUDE_DIRS})
    include_directories(${GAME_SOURCE_DIRECTORY})

    add_executable(${CMAKE_PROJECT_NAME} ${GAME_CPP_SOURCES})

    target_link_libraries(${CMAKE_PROJECT_NAME} ${ALLEGRO_LIBRARIES})
endif(WANT_ANDROID)
