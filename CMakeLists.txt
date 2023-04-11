cmake_minimum_required(VERSION 3.5)

project(briscola_scoperta)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the include directories
include_directories(include)

# Add the source files
add_executable(briscola_scoperta
    src/card.cpp
    src/game.cpp
    src/main.cpp
    src/player.cpp
    src/table.cpp
)

# Add any required libraries (if necessary)
# target_link_libraries(my_executable_name library_name)

# Install the executable (if necessary)
# install(TARGETS my_executable_name DESTINATION bin)
