cmake_minimum_required (VERSION 2.8.8)
project (Ballsy)

option(WANT_ANDROID "Build for Android" OFF)

set(GAME_FILE_DIRECTORY "Ballsy")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall") 
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(GAME_SOURCES
    src/main.cpp
    #src/main.c
    #src/common.c
    #src/ex_bitmap.c
    )

if(WANT_ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DANDROID=1") 
    set(ANDROID_TARGET "android-15" CACHE STRING "What Android target to compile for.")
    include(${CMAKE_SOURCE_DIR}/cmake/Android.cmake)
else()
    file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets/)

    find_package(Allegro5 REQUIRED)

    include_directories(${ALLEGRO_INCLUDE_DIRS})
    include_directories("${CMAKE_SOURCE_DIR}/include")

    add_executable(${CMAKE_PROJECT_NAME} ${GAME_SOURCES})

    target_link_libraries(${CMAKE_PROJECT_NAME} ${ALLEGRO_LIBRARIES})
endif(WANT_ANDROID)



#add_subdirectory (src)
#add_subdirectory (test)

