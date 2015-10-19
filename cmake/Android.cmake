set(ANDROID_NDK_TOOLCHAIN_ROOT "$ENV{TC}" CACHE PATH "Path to the Android NDK Standalone Toolchain" )

message( STATUS "Selected Android toolchain: ${ANDROID_NDK_TOOLCHAIN_ROOT}" )
if(NOT EXISTS ${ANDROID_NDK_TOOLCHAIN_ROOT})
   set(ANDROID_NDK_TOOLCHAIN_ROOT "/opt/android-toolchain" CACHE PATH "Path to the Android NDK Standalone Toolchain" )
   message( STATUS "Using default path for toolchain ${ANDROID_NDK_TOOLCHAIN_ROOT}")
   message( STATUS "If you prefer to use a different location, please set the ANDROID_NDK_TOOLCHAIN_ROOT cmake variable.")
endif()
   
#set(ANDROID_NDK_TOOLCHAIN_ROOT ${ANDROID_NDK_TOOLCHAIN_ROOT} CACHE PATH
#    "root of the android ndk standalone toolchain" FORCE)
    
if(NOT EXISTS ${ANDROID_NDK_TOOLCHAIN_ROOT})
  message(FATAL_ERROR
  "${ANDROID_NDK_TOOLCHAIN_ROOT} does not exist!
  You should either set an environment variable:
    export ANDROID_NDK_TOOLCHAIN_ROOT=~/my-toolchain
  or put the toolchain in the default path:
    sudo ln -s ~/android-toolchain /opt/android-toolchain
    ")
endif()
    
find_program(ANDROID_TOOL android NAMES android android.bat CMAKE_FIND_ROOT_PATH_BOTH)
find_program(NDK_BUILD ndk-build CMAKE_FIND_ROOT_PATH_BOTH)
find_program(ANT ant CMAKE_FIND_ROOT_PATH_BOTH)
set(ANT_COMMAND "${ANT}" -noinput -nouserlib -noclasspath -quiet)
set(ANDROID_UPDATE_COMMAND "${ANDROID_TOOL}" update project -p . -t ${ANDROID_TARGET})

if(NOT ANDROID_TOOL)
    message(FATAL_ERROR "android tool not found")
endif()
if(NOT NDK_BUILD)
    message(FATAL_ERROR "ndk-build not found")
endif()
if(NOT ANT)
    message(FATAL_ERROR "ant not found")
endif()

set(prog "Ballsy")
set(prog_target ${prog})
set(package "org.liballeg.examples.${prog}")
set(package_slash "org/liballeg/examples/${prog}")
set(activity "Activity")

# The Android project directory.
set(project_dir "${CMAKE_CURRENT_BINARY_DIR}/${prog}.project")
set(project_apk "${project_dir}/bin/example-debug.apk")

set(ALLEGRO_JAR_PATH "${project_dir}/allegro")
set(ALLEGRO_LIB_TYPE_SUFFIX "-debug")

file(COPY ${CMAKE_SOURCE_DIR}/android-wrapper/ DESTINATION ${project_dir})
file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${project_dir}/assets/)

set(ANDROID_SOURCE_DIR_PREFIX "c")
set(ANDROID_CPP_SOURCES "")
foreach(f ${GAME_CPP_SOURCES})
    LIST(APPEND ANDROID_CPP_SOURCES "../${ANDROID_SOURCE_PREFIX}${f}")
endforeach(f)
string (REPLACE ";" "," ANDROID_CPP_SOURCES "${ANDROID_CPP_SOURCES}")

set(ANDROID_ALL_SOURCES "")
foreach(f ${GAME_ALL_SOURCES})
    LIST(APPEND ANDROID_ALL_SOURCES "${project_dir}/${ANDROID_SOURCE_PREFIX}${f}")

    add_custom_command(
        OUTPUT ${project_dir}/${ANDROID_SOURCE_PREFIX}${f}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${f} ${project_dir}/${ANDROID_SOURCE_PREFIX}${f}
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${f})
endforeach(f)

add_custom_command(
    OUTPUT ${project_dir}/local.properties
    WORKING_DIRECTORY ${project_dir}
    COMMAND ${ANDROID_UPDATE_COMMAND}
    VERBATIM
    )

configure_file(
    ${project_dir}/localgen.properties.in
    ${project_dir}/localgen.properties
    )

configure_file(
    ${project_dir}/project.properties.in
    ${project_dir}/project.properties
    @ONLY
    )

configure_file(
    ${project_dir}/jni/localgen.mk.in
    ${project_dir}/jni/localgen.mk
    )
 
message(STATUS "CPP: ${ANDROID_CPP_SOURCES}")
message(STATUS "ALL: ${ANDROID_ALL_SOURCES}")

add_custom_command(
    OUTPUT ${project_apk}
    DEPENDS ${project_dir}/local.properties
    DEPENDS ${ANDROID_ALL_SOURCES}
    WORKING_DIRECTORY ${project_dir}
    COMMAND ${NDK_BUILD}
    COMMAND ${ANT_COMMAND} debug
    )

add_custom_target(apk
    ALL
    DEPENDS ${project_apk}
    )

#-----------------------------------------------------------------------------#

add_custom_target(install_apk
    DEPENDS ${project_apk}
    WORKING_DIRECTORY ${project_dir}
    COMMAND adb -d install -r ${project_apk}
    )

add_custom_target(run_apk
    DEPENDS install_apk
    COMMAND adb -d shell
            'am start -a android.intent.action.MAIN -n org.liballeg.example/.ExampleActivity'
    )
