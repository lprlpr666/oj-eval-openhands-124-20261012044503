cmake_minimum_required(VERSION 3.10)
project(train_ticket_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(code solution.cpp)

# Set optimization flags
set_target_properties(code PROPERTIES
    CXX_FLAGS "-O2 -Wall -Wextra"
)

# For GCC/Clang, add specific optimizations
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(code PRIVATE -O2 -Wall -Wextra -static)
endif()