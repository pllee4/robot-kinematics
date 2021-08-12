# set minimum version required for cmake
cmake_minimum_required(VERSION 3.10.2)

# set the project name and version
project(robot_kinematics VERSION 1.0.0)

set(USER_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${USER_CMAKE_PATH}/modules")
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu/cmake")

include(GNUInstallDirs)

# find dependency
find_package(PkgConfig REQUIRED) 
pkg_check_modules(Cairo REQUIRED IMPORTED_TARGET cairo)

## Put all binary files into /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(third_party)
add_subdirectory(src)