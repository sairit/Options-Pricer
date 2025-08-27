cmake_minimum_required(VERSION 3.10)
project(OptionsPricer LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files (shared between executables)
set(SOURCES
    src/BinomialTreeEngine.cpp
    src/BlackScholesEngine.cpp
    src/Option.cpp
    src/Payoff.cpp
)

# Main executable
add_executable(OptionsPricer src/main.cpp ${SOURCES})
target_compile_options(OptionsPricer PRIVATE -Wall -Wextra -pedantic)

# Tests executable
enable_testing()
add_executable(OptionsPricerTests test/tests.cpp ${SOURCES})
target_include_directories(OptionsPricerTests PRIVATE include)
add_test(NAME OptionsPricerTests COMMAND OptionsPricerTests)
