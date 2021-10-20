cmake_minimum_required(VERSION 3.7)
#common resource names
project(dde-online-accounts-plugin-test)

ADD_COMPILE_OPTIONS(-fno-access-control)

set(APP_CLIENT_DIR "${CMAKE_SOURCE_DIR}/dde-online-accounts/doa-plugin")

set(APP_BIN_NAME "dde-online-accounts-plugin-test")

find_package(PkgConfig REQUIRED)
find_package(DtkCore REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(DtkWidget REQUIRED)
find_package(DtkGui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(GTest REQUIRED)
find_package(Qt5Test REQUIRED)
 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--as-needed -fPIE")
set(CMAKE_EXE_LINKER_FLAGS "-pie")

include_directories(${APP_CLIENT_DIR}/src)

SUBDIRLIST(all_src ${APP_CLIENT_DIR}/src)

#Include all app own subdirectorys
foreach(subdir ${all_src})
    include_directories(${APP_CLIENT_DIR}/src/${subdir})
endforeach()

file(GLOB_RECURSE DOA_PLUGIN_SRC ${APP_CLIENT_DIR}/src/*.cpp)
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})
list(REMOVE_ITEM DOA_PLUGIN_SRC ${APP_CLIENT_DIR}/src/main.cpp)

#test SRC
SUBDIRLIST(TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
foreach(subdir ${TEST_SRC})
    include_directories(${subdir})
endforeach()

file(GLOB_RECURSE DOA_PLUGIN_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
include_directories("${CMAKE_SOURCE_DIR}/dde-online-accounts/doa-lib/src")

list(APPEND CMAKE_MODULE_PATH "${ASAN_CMAKE_DIR}")

# Tell CMake to create the executable
add_executable(${APP_BIN_NAME} ${DOA_PLUGIN_TEST_SRC} ${DOA_PLUGIN_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
    "/usr/include/dde-control-center"
    ${DtkWidget_INCLUDE_DIRS}
    ${OBJECT_BINARY_DIR})

target_link_libraries(${APP_BIN_NAME}
    ${DtkWidget_LIBRARIES}
    ${DtkCore_LIBRARIES}
    ${DtkGui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
    ${Qt5Network_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Qt5::Test
    pthread
    doa-lib
)
