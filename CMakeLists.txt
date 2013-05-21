#
# Linux:
#
#  mkdir -p build
#  cd build
#  cmake ..
#  make
#
# Windows:
#
#  mkdir -p build-mingw32
#  cd build-mingw32
#  cmake .. \
#       -DCMAKE_TOOLCHAIN_FILE=../basic-mingw32.cmake \
#       -DCMAKE_INSTALL_PREFIX=/neco/nekam \
#  make
#  make install
#

cmake_minimum_required(VERSION 2.8)
project(Drex)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules")

if(NOT WIN32)
    set(DREX_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
else()
    set(DREX_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}")
endif()

add_subdirectory(src)

install(DIRECTORY data DESTINATION "${DREX_INSTALL_DIR}")
install(DIRECTORY maps DESTINATION "${DREX_INSTALL_DIR}")
install(DIRECTORY users DESTINATION "${DREX_INSTALL_DIR}")
