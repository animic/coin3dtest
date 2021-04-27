
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core Widgets Gui Charts PrintSupport)

set(PROJECT_NAME test01)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable (test01_sub main_sub.cpp)
add_executable (test01_pub main_pub.cpp)
