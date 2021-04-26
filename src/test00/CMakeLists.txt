
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core Widgets Gui Charts PrintSupport)

set(PROJECT_NAME test00)

aux_source_directory(. PROJ_SRCS)

FILE(GLOB Project_UIS "*.ui")
FILE(GLOB Project_QRCS "*.qrc")
FILE(GLOB Project_QMLS "*.qml")
FILE(GLOB Project_RCS "*.rc")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable (${PROJECT_NAME} ${PROJ_SRCS}
${Project_UIS}
${Project_QRCS}
${Project_QMLS}
${Project_RCS}
)
