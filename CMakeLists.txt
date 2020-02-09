cmake_minimum_required(VERSION 3.15)

project(
  drawsource
  DESCRIPTION "Widget for drawing pixels"
  HOMEPAGE_URL "kszk.bme.hu"
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt5
  COMPONENTS Widgets Network
  REQUIRED)

add_executable(
  ${PROJECT_NAME} src/drawsender.cpp src/drawsender.h src/drawsender.ui
                  src/griddrawer.cpp src/griddrawer.h src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network
                                              libmueb::muebtransmitter)

set(CPACK_PACKAGE_VENDOR "PROJECT_HOMEPAGE_URL")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
# set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
include(CPack)
