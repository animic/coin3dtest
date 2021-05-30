cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(PROJ_NAME test03)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

aux_source_directory(. PROJ_SRCS)
FILE(GLOB Project_UIS "*.ui")
FILE(GLOB Project_QRCS "*.qrc")
FILE(GLOB Project_QMLS "*.qml")
FILE(GLOB Project_RCS "*.rc")

LIST(APPEND PROJ_SRCS ${Project_UIS})
LIST(APPEND PROJ_SRCS ${Project_QRCS})
LIST(APPEND PROJ_SRCS ${Project_QMLS})
LIST(APPEND PROJ_SRCS ${Project_RCS})

add_executable(${PROJ_NAME} MACOSX_BUNDLE ${PROJ_SRCS})
target_link_libraries(${PROJ_NAME} PRIVATE ${VTK_LIBRARIES} Qt5::Widgets Qt5::OpenGL Qt5::Charts)
