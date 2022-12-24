cmake_minimum_required( VERSION 3.11 )
project( fauxpos )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

find_package( Qt5 COMPONENTS Core Widgets REQUIRED )

file( GLOB_RECURSE ui_files ui/*.ui )
QT5_WRAP_UI( ui_files ${ui_files} )

file( GLOB_RECURSE files src/*.h src/*.cpp res/resources.qrc )
add_executable( ${PROJECT_NAME} ${files} ${ui_files} )

target_link_libraries( ${PROJECT_NAME} Qt5::Widgets )
include_directories( ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} )
