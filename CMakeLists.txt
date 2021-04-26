cmake_minimum_required (VERSION 3.12)

project(APP)

set (APP_VERSION_MAJOR 0)
set (APP_VERSION_MINOR 0)
set (APP_VERSION_PATCH 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/include/config.h.in"
  "${PROJECT_BINARY_DIR}/include/config.h"
  )

include(./cmake/print_all_variables.cmake)

option(FOO_APP_CONSOLE "App Use Console" OFF)

IF(FOO_DEVELOPING)
add_definitions(-D__DEVELOPING__=1)
ELSE()
add_definitions(-D__DEVELOPING__=0)
ENDIF()


FIND_PACKAGE(OpenCV)
FIND_PACKAGE(tiff REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(coin CONFIG REQUIRED)
find_package(soqt CONFIG REQUIRED)

add_definitions(-DUNICODE -D_UNICODE)

include_directories(${TIFF_INCLUDE_DIR})
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/Common)
include_directories(${PROJECT_SOURCE_DIR}/src/util)
include_directories(${PROJECT_SOURCE_DIR}/src/App)
include_directories(${PROJECT_SOURCE_DIR}/src/ModuleSynchronizer)
include_directories(${PROJECT_SOURCE_DIR}/src/ModuleCamera)

link_libraries(${OpenCV_LIBS})
link_libraries(${OpenCV_LIB_COMPONENTS})
link_libraries(${TIFF_LIBS})
link_libraries(nlohmann_json::nlohmann_json)
link_libraries(Coin::Coin)
link_libraries(SoQt::SoQt)

add_subdirectory(src/test00)

enable_testing()
ADD_TEST(NAME test00 COMMAND test00)

