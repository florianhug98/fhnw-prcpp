cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(Bitmap)

# Define a variable with all header files
set(Bitmap_INC
    ./Bitmap/Bitmap.h
    )

# Define a variable with all implementation files
set(Bitmap_SRC
    ./Bitmap/Bitmap.cpp
    )

# Built binaries are output at ./bin/Debug
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug")

# Define the build target "bitmap", a static library depending on all source files
add_library(bitmap STATIC ${Bitmap_SRC} ${Bitmap_INC})
# Add an include directory to allow imports to work properly
target_include_directories(bitmap PUBLIC "${PROJECT_SOURCE_DIR}/Bitmap")

# Create the main executable and link to library
add_executable(console ./Console/main.cpp)
target_include_directories(console PUBLIC "${PROJECT_SOURCE_DIR}/Bitmap")
target_link_libraries(console PUBLIC bitmap)

# Enable strict compiler warnings
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(console PRIVATE -Wall -Wextra)
endif()
if ( MSVC )
    target_compile_options(console PRIVATE /W4)
endif()

# Add test implementation files
set(Bitmap_TEST_SRC
    ./UnitTest2/UnitTestBitmap.cpp
)

# Fetch Google Test dependency from GitHub
include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# [Windows] Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create a text executable
add_executable(unittest2 ${Bitmap_TEST_SRC})
# Link executable with our main library and the Google Test library
target_link_libraries(unittest2 bitmap GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unittest2)
