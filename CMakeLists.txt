cmake_minimum_required (VERSION 4.0.0)
include(ExternalProject)

project (imMinipro VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
include_directories(${SDL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++23")


# imgui
file (GLOB imgui_cpp "${PROJECT_SOURCE_DIR}/lib/imgui/*.cpp")
include_directories("${PROJECT_SOURCE_DIR}/lib/imgui/")


# minipro
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS "Windows_NT")
else()
    set(OS "NotWin")
endif()

execute_process(
    COMMAND make library OS=${OS} CFLAGS+=-DDEBUG_USB
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/minipro/
)

ExternalProject_Add(
    ext_minipro
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/minipro/
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make library CXX=${CMAKE_CXX_COMPILER} CXXFLAGS=${CMAKE_CXX_FLAGS}
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
    STEP_TARGETS build
    BUILD_BYPRODUCTS ${PROJECT_SOURCE_DIR}/lib/minipro/src/libminipro.a
)

#add_custom_target(minipro_lib_t ALL DEPENDS minipro_lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/minipro/src/)


add_library(minipro STATIC IMPORTED)
#ExternalProject_Get_Property(ext_minipro source_dir)
set_property(TARGET minipro PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/minipro/src/libminipro.a)
add_dependencies(minipro ext_minipro-build)


# src
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
file (GLOB_RECURSE source_files "${source_dir}/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/src/)

include_directories(${PROJECT_SOURCE_DIR}/src/usb)

include_directories(${PROJECT_SOURCE_DIR}/src/menubar)

include_directories(${PROJECT_SOURCE_DIR}/src/modals)
include_directories(${PROJECT_SOURCE_DIR}/src/modals/about)
include_directories(${PROJECT_SOURCE_DIR}/src/modals/programmer)

include_directories(${PROJECT_SOURCE_DIR}/src/windows)
include_directories(${PROJECT_SOURCE_DIR}/src/windows/manage-programmer)
include_directories(${PROJECT_SOURCE_DIR}/src/windows/device-list)
include_directories(${PROJECT_SOURCE_DIR}/src/windows/settings)


add_executable (imMinipro ${imgui_cpp} ${source_files})

target_compile_definitions(imMinipro PRIVATE IMMINI_VERSION="${PROJECT_VERSION}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(imMinipro PRIVATE DEBUG)
endif()


target_link_libraries(imMinipro SDL3::SDL3 OpenGL::GL usb-1.0 ZLIB::ZLIB minipro)
