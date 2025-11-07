# CMakeList.txt : CMake project for prcpp, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME Console)

# Add source to this project's executable.
add_executable(${TARGET_NAME} "main.cpp" "../Strings/MyString.cpp" "../Strings/MyString.h" "../Strings/StringView.h")
target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Strings")
