cmake_minimum_required(VERSION 3.10)
project(OptionsPricer LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/BinomialTreeEngine.cpp
    src/Option.cpp
    src/Payoff.cpp
)

# Add the main executable
add_executable(OptionsPricer ${SOURCES})

# Compiler options
target_compile_options(OptionsPricer PRIVATE -Wall -Wextra -pedantic)

# Add tests
enable_testing()
add_executable(OptionsPricerTests test/option_tests.cpp src/Payoff.cpp src/Option.cpp)
target_include_directories(OptionsPricerTests PRIVATE include)
add_test(NAME OptionsPricerTests COMMAND OptionsPricerTests)