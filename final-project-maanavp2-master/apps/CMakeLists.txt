get_filename_component(CINDER_PATH "/Users/maanav18/Downloads/cinder_0.9.2_mac/proj/cmake/modules/../../../" ABSOLUTE)
include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${FinalProject_SOURCE_DIR}/apps/*.h"
        "${FinalProject_SOURCE_DIR}/apps/*.hpp"
        "${FinalProject_SOURCE_DIR}/apps/*.cc"
        "${FinalProject_SOURCE_DIR}/apps/*.cpp")

find_library(FRAMEWORK_EDSDK
        NAMES EDSDK
        PATHS ${FinalProject_SOURCE_DIR}
        PATH_SUFFIXES Frameworks)

if (${FRAMEWORK_EDSDK} STREQUAL FRAMEWORK_EDSDK-NOTFOUND)
    message("framework wasn't found")
endif ()

ci_make_app(
        APP_NAME cinder-myapp
        CINDER_PATH ${CINDER_PATH}
        SOURCES ${SOURCE_LIST}
        LIBRARIES mylibrary opencv gflags
        BLOCKS Cinder-CanonSdk
)

target_link_libraries(cinder-myapp "${FRAMEWORK_EDSDK}/EDSDK")
target_compile_features(cinder-myapp PRIVATE cxx_std_14)

# Cross-platform compiler lints
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
        OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(cinder-myapp PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    cmake_policy(SET CMP0015 NEW)
    target_compile_options(cinder-myapp PRIVATE
            /W3)
endif ()
add_custom_command(TARGET cinder-myapp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${FinalProject_SOURCE_DIR}/Frameworks/EDSDK.framework
        ${FinalProject_SOURCE_DIR}/cmake-build-debug/Debug/cinder-myapp/cinder-myapp.app/Contents/Frameworks/EDSDK.framework
        )